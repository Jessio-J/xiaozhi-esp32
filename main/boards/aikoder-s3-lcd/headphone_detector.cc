#include <esp_system.h>
#include <esp_err.h>
#include <driver/gpio.h>
#include <esp_log.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_check.h"

#include "headphone_detector.h"

#define HEADPHONE_DETECTOR_TAG "HeadphoneDetector"
#define HEADPHONE_DETECTOR_TASK_STACK_SIZE 3072
#define HEADPHONE_DETECTOR_TASK_PRIORITY 5

static const char *TAG = HEADPHONE_DETECTOR_TAG;

HeadphoneDetector::HeadphoneDetector(gpio_num_t headphone_gpio_num, gpio_num_t pa_gpio_num)
    : headphone_gpio_(headphone_gpio_num),
      pa_gpio_(pa_gpio_num),
      event_queue_(nullptr),
      detector_task_handle_(nullptr)
{
    ESP_LOGD(TAG, "HeadphoneDetector object created for GPIO%d and PA GPIO%d", headphone_gpio_, pa_gpio_);
}

HeadphoneDetector::~HeadphoneDetector()
{
    ESP_LOGI(TAG, "Deinitializing Headphone Detector...");
    // Remove ISR handler
    gpio_isr_handler_remove(headphone_gpio_);
    ESP_LOGD(TAG, "ISR handler removed for GPIO%d", headphone_gpio_);

    // Delete task
    if (detector_task_handle_ != nullptr)
    {
        vTaskDelete(detector_task_handle_);
        ESP_LOGD(TAG, "Detector task deleted.");
    }

    // Delete queue
    if (event_queue_ != nullptr)
    {
        vQueueDelete(event_queue_);
        ESP_LOGD(TAG, "Event queue deleted.");
    }

    ESP_LOGI(TAG, "Headphone Detector deinitialized.");
}

esp_err_t HeadphoneDetector::Initialize()
{
    ESP_LOGI(TAG, "Initializing Headphone Detector (GPIO%d) and PA Control (GPIO%d)...", headphone_gpio_, pa_gpio_);

    esp_err_t ret;

    // 0. Create event queue
    event_queue_ = xQueueCreate(1, sizeof(HeadphoneEvent));
    ESP_RETURN_ON_FALSE(event_queue_ != nullptr, ESP_FAIL, TAG, "Failed to create event queue");
    ESP_LOGD(TAG, "Event queue created.");

    // 1. Create processing task
    BaseType_t task_created = xTaskCreate(
        headphone_detector_task,            // Task function
        "HPDetectTask",                     // Task name
        HEADPHONE_DETECTOR_TASK_STACK_SIZE, // Stack size
        this,                               // Parameter to pass (this pointer)
        HEADPHONE_DETECTOR_TASK_PRIORITY,   // Task priority
        &detector_task_handle_              // Task handle
    );
    ESP_RETURN_ON_FALSE(task_created == pdPASS, ESP_FAIL, TAG, "Failed to create detector task");
    ESP_LOGD(TAG, "Detector task created.");

    // 2. Configure PA pin as output (optional, depending on if the callback handles it)
    // Keeping this here allows setDefaultPaAction to work.
    ret = gpio_set_direction(pa_gpio_, GPIO_MODE_OUTPUT);
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to set PA GPIO%d direction", pa_gpio_);
    ESP_LOGD(TAG, "PA GPIO%d configured as output.", pa_gpio_);

    // 3. Configure Headphone Detect pin as input with pull-up
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << headphone_gpio_),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE, // Enable pull-up as per requirement (GPIO3 HIGH when unplugged)
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_ANYEDGE, // Detect both plug (falling edge) and unplug (rising edge)
    };
    ret = gpio_config(&io_conf);
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to config Headphone Detect GPIO%d", headphone_gpio_);
    ESP_LOGD(TAG, "Headphone Detect GPIO%d configured with pull-up and any-edge interrupt.", headphone_gpio_);

    // 4. Install GPIO ISR service
    // This needs to be called once before adding any ISR handlers.
    // Button class might already do this, but calling it again is safe (returns ESP_ERR_INVALID_STATE).
    ret = gpio_install_isr_service(0); // Use default configuration
    if (ret != ESP_OK && ret != ESP_ERR_INVALID_STATE)
    {
        ESP_LOGE(TAG, "Failed to install GPIO ISR service: %s", esp_err_to_name(ret));
        return ret; // Return error if service installation truly failed
    }
    else if (ret == ESP_OK)
    {
        ESP_LOGD(TAG, "GPIO ISR service installed.");
    }
    else
    {
        ESP_LOGD(TAG, "GPIO ISR service already installed.");
    }

    // 5. Add ISR handler for the headphone detect pin
    // Pass 'this' pointer so the static handler can call the member function
    ret = gpio_isr_handler_add(headphone_gpio_, headphone_isr_handler, (void *)this);
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to add ISR handler for GPIO%d", headphone_gpio_);
    ESP_LOGD(TAG, "ISR handler added for GPIO%d.", headphone_gpio_);

    // 6. Read initial state and trigger event processing in the task
    // This handles the case where headphones are already plugged in at boot.
    HeadphoneEvent initial_event = {};
    xQueueSend(event_queue_, &initial_event, 0); // Send event to process initial state (don't wait)
    ESP_LOGI(TAG, "Sent initial event to queue.");

    ESP_LOGI(TAG, "Headphone Detector initialization complete.");
    return ESP_OK;
}

void HeadphoneDetector::setCallback(std::function<void(HeadphoneState state)> cb)
{
    callback_ = cb;
    ESP_LOGD(TAG, "User callback set.");
    // You might want to immediately trigger the callback with the current state
    // after setting it, in case the state changed before the callback was set.
    // ProcessEvent(); // Call directly or send a message to the queue
}

HeadphoneState HeadphoneDetector::getCurrentState() const
{
    return gpio_get_level(headphone_gpio_) == 0 ? HeadphoneState::PLUGGED_IN : HeadphoneState::UNPLUGGED;
}

void HeadphoneDetector::setDefaultPaAction(HeadphoneState state) const
{
    if (state == HeadphoneState::PLUGGED_IN)
    {
        ESP_LOGI(TAG, "Default PA Action: Headphones PLUGGED IN, setting PA GPIO%d Low (Speaker Off)", pa_gpio_);
        gpio_set_level(pa_gpio_, 0); // Set PA pin LOW to disable speaker amplifier
    }
    else
    {
        ESP_LOGI(TAG, "Default PA Action: Headphones UNPLUGGED, setting PA GPIO%d High (Speaker On)", pa_gpio_);
        gpio_set_level(pa_gpio_, 1); // Set PA pin HIGH to enable speaker amplifier
    }
}

void IRAM_ATTR HeadphoneDetector::headphone_isr_handler(void *arg)
{
    BaseType_t higher_priority_task_woken = pdFALSE;
    HeadphoneEvent event = {};
    // Send event to the queue. Don't block.
    // If the queue is full, the event is dropped, which is acceptable for state changes
    // if the task reads the *current* state from the GPIO anyway.
    xQueueSendFromISR(static_cast<HeadphoneDetector *>(arg)->event_queue_, &event, &higher_priority_task_woken);

    // If sending to the queue woke a higher priority task, yield from ISR
    if (higher_priority_task_woken)
    {
        portYIELD_FROM_ISR();
    }
}

void HeadphoneDetector::headphone_detector_task(void *pvParameter)
{
    HeadphoneDetector *detector = static_cast<HeadphoneDetector *>(pvParameter);
    HeadphoneEvent event;

    ESP_LOGD(TAG, "Headphone detector task started.");

    while (true)
    {
        // Wait for an event from the ISR (or initial event)
        if (xQueueReceive(detector->event_queue_, &event, portMAX_DELAY) == pdTRUE)
        {
            // Process the event in the task context
            detector->ProcessEvent();
        }
        // You could add a short vTaskDelay(1) here if you want to ensure
        // other lower priority tasks get a chance, though portMAX_DELAY
        // on a queue generally handles this.
    }
    vTaskDelete(nullptr); // Task exits here if loop breaks
}

void HeadphoneDetector::ProcessEvent()
{
    // Read the current state of the headphone detect pin
    HeadphoneState currentState = getCurrentState();

    // Log the detected state
    ESP_LOGI(TAG, "Detected state change. Current state: %s",
             (currentState == HeadphoneState::PLUGGED_IN ? "PLUGGED_IN (Low)" : "UNPLUGGED (High)"));

    // Call the user-provided callback if it is set
    if (callback_)
    {
        ESP_LOGD(TAG, "Calling user callback...");
        try
        {
            callback_(currentState); // Pass the current state to the callback
        }
        catch (const std::exception &e)
        {
            ESP_LOGE(TAG, "Exception in user callback: %s", e.what());
            // Handle callback errors if necessary
        }
        catch (...)
        {
            ESP_LOGE(TAG, "Unknown exception in user callback.");
            // Handle other potential exceptions
        }
    }
    else
    {
        ESP_LOGW(TAG, "No user callback set for headphone state change.");
        // Optionally, perform a default action if no callback is set
        // setDefaultPaAction(currentState);
    }

    // Optionally, you can perform the default PA action here regardless of callback,
    // or leave it entirely to the callback. Let's leave it to the callback for maximum flexibility.
    // If the user wants the default PA action, they should call setDefaultPaAction
    // inside their callback.
}

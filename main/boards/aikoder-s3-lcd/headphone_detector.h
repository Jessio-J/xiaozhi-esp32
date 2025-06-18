#ifndef _HEADPHONE_DETECTOR_H
#define _HEADPHONE_DETECTOR_H

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include <functional>

enum class HeadphoneState
{
    UNPLUGGED = 0,  // Corresponds to GPIO High
    PLUGGED_IN = 1, // Corresponds to GPIO Low
};

struct HeadphoneEvent {
    // Currently, just signaling that *some* change occurred is enough.
    // The task will read the pin state itself.
    // If needed, you could pass the timestamp or the raw pin level here.
    int raw_level;
};

class HeadphoneDetector
{
private:
    gpio_num_t headphone_gpio_;
    gpio_num_t pa_gpio_;

    // The callback takes the new state (plugged in or unplugged) as argument
    std::function<void(HeadphoneState state)> callback_;

    QueueHandle_t event_queue_;
    TaskHandle_t detector_task_handle_;

    // Static ISR handler (required by ESP-IDF GPIO ISR API)
    // Declared here, defined in the .cc file
    static void IRAM_ATTR headphone_isr_handler(void *arg);

    static void headphone_detector_task(void* pvParameter);

    void ProcessEvent();

public:
    // Constructor
    // Takes headphone detect pin and PA control pin numbers as arguments
    HeadphoneDetector(gpio_num_t headphone_gpio_num, gpio_num_t pa_gpio_num);
    ~HeadphoneDetector();

    esp_err_t Initialize();
    void setCallback(std::function<void(HeadphoneState state)> cb);

    HeadphoneState getCurrentState() const;

    void setDefaultPaAction(HeadphoneState state) const;
};

#endif // _HEADPHONE_DETECTOR_H

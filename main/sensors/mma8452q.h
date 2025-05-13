#pragma once

#include "../boards/common/i2c_device.h"
#include <driver/gpio.h>
#include <esp_attr.h>      // 添加这个头文件用于IRAM_ATTR
#include <freertos/FreeRTOS.h>  // 添加这个头文件用于pdMS_TO_TICKS
#include <freertos/task.h>  // 添加这个头文件用于xTaskCreate
#include <freertos/queue.h> // 添加这个头文件用于QueueHandle_t
#include <functional>

class MMA8452Q : public I2cDevice {
public:
    MMA8452Q(i2c_master_bus_handle_t i2c_bus, gpio_num_t int1_pin);
    ~MMA8452Q();

    bool Initialize();
    void OnShake(std::function<void()> callback);

private:
    static void IRAM_ATTR HandleInterrupt(void* arg);  // 中断处理函数
    void ProcessInterrupt();  // 无参数版本
    void ProcessInterrupt(uint8_t gpio_num);  // 带GPIO参数版本

    static void UpdateTask(void* arg);  // FreeRTOS任务函数
    static void user_task_interrupt(void* arg);  // FreeRTOS任务函数
    gpio_num_t int1_pin_;
    std::function<void()> shake_callback_;
    static constexpr uint8_t I2C_ADDR = 0x1C;  // SA0接地时的地址
    volatile bool interrupt_triggered_ = false;  // 中断标志位
    TaskHandle_t update_task_handle_ = nullptr;  // 任务句柄
    QueueHandle_t gpio_evt_queue = nullptr;  // 事件队列句柄
};
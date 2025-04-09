#ifndef _SMARTCONFIG_H_
#define _SMARTCONFIG_H_

#include <functional>
#include "esp_event.h"
#include <string>
#include "freertos/event_groups.h"

// 事件标志位定义
#define CONNECTED_BIT      BIT0
#define ESPTOUCH_DONE_BIT  BIT1

class SmartConfig {
public:
    // 获取单例实例
    static SmartConfig& GetInstance();

    // 启动智能配网
    void Start();

    // 设置WiFi连接成功回调
    void OnConnected(std::function<void()> callback) { on_connected_ = callback; }

    // 设置配网完成回调
    void OnConfigDone(std::function<void()> callback) { on_config_done_ = callback; }

    // 删除拷贝构造函数和赋值运算符
    SmartConfig(const SmartConfig&) = delete;
    SmartConfig& operator=(const SmartConfig&) = delete;

private:
    // 私有构造函数和析构函数
    SmartConfig();
    ~SmartConfig();

    // WiFi事件处理函数
    static void EventHandler(void* arg, esp_event_base_t event_base,
                           int32_t event_id, void* event_data);

    // 启动智能配网任务
    void StartSmartConfigTask();

    // 成员变量
    EventGroupHandle_t event_group_ = nullptr;
    bool is_running_ = false;
    std::function<void()> on_connected_ = nullptr;
    std::function<void()> on_config_done_ = nullptr;
    std::string ssid_;
    std::string password_;
};

#endif // _SMARTCONFIG_H_
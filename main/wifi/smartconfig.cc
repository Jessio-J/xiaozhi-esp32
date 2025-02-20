#include "smartconfig.h"
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_eap_client.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_smartconfig.h"
#include "esp_mac.h"
#include "ssid_manager.h"
static const char *TAG = "smartconfig";

SmartConfig& SmartConfig::GetInstance() {
    static SmartConfig instance;
    return instance;
}

SmartConfig::SmartConfig() {
    event_group_ = xEventGroupCreate();
}

SmartConfig::~SmartConfig() {
    if (event_group_) {
        vEventGroupDelete(event_group_);
    }
}

/**
 * WiFi事件处理函数
 * @param arg 参数指针
 * @param event_base 事件基类
 * @param event_id 事件ID
 * @param event_data 事件数据
 */
void SmartConfig::EventHandler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    auto* this_ = static_cast<SmartConfig*>(arg);
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        this_->StartSmartConfigTask();
    } 
    // WiFi断开连接事件
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        // 尝试重新连接WiFi
        esp_wifi_connect();
        // 清除连接状态位
        xEventGroupClearBits(this_->event_group_, CONNECTED_BIT);
    } 
    // 获取IP地址事件
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        // 设置连接状态位
        xEventGroupSetBits(this_->event_group_, CONNECTED_BIT);
    } 
    // 智能配网扫描完成事件
    else if (event_base == SC_EVENT && event_id == SC_EVENT_SCAN_DONE) {
        ESP_LOGI(TAG, "Scan done");
    } 
    // 智能配网发现信道事件
    else if (event_base == SC_EVENT && event_id == SC_EVENT_FOUND_CHANNEL) {
        ESP_LOGI(TAG, "Found channel");
    } 
    // 智能配网获取SSID和密码事件
    else if (event_base == SC_EVENT && event_id == SC_EVENT_GOT_SSID_PSWD) {
        ESP_LOGI(TAG, "Got SSID and password");

        // 获取配网数据
        smartconfig_event_got_ssid_pswd_t *evt = (smartconfig_event_got_ssid_pswd_t *)event_data;
        wifi_config_t wifi_config;
        uint8_t ssid[33] = { 0 };
        uint8_t password[65] = { 0 };
        uint8_t rvd_data[33] = { 0 };

        // 清空配置结构体
        bzero(&wifi_config, sizeof(wifi_config_t));
        // 复制SSID和密码到配置结构体
        memcpy(wifi_config.sta.ssid, evt->ssid, sizeof(wifi_config.sta.ssid));
        memcpy(wifi_config.sta.password, evt->password, sizeof(wifi_config.sta.password));

#ifdef CONFIG_SET_MAC_ADDRESS_OF_TARGET_AP
        // 设置目标AP的MAC地址
        wifi_config.sta.bssid_set = evt->bssid_set;
        if (wifi_config.sta.bssid_set == true) {
            ESP_LOGI(TAG, "Set MAC address of target AP: "MACSTR" ", MAC2STR(evt->bssid));
            memcpy(wifi_config.sta.bssid, evt->bssid, sizeof(wifi_config.sta.bssid));
        }
#endif

        // 复制SSID和密码到本地变量和成员变量
        memcpy(ssid, evt->ssid, sizeof(evt->ssid));
        memcpy(password, evt->password, sizeof(evt->password));
        this_->ssid_ = std::string((char*)ssid);
        this_->password_ = std::string((char*)password);
        ESP_LOGI(TAG, "SSID:%s", ssid);
        ESP_LOGI(TAG, "PASSWORD:%s", password);

        // 如果是ESPTOUCH V2版本，获取额外数据
        if (evt->type == SC_TYPE_ESPTOUCH_V2) {
            ESP_ERROR_CHECK( esp_smartconfig_get_rvd_data(rvd_data, sizeof(rvd_data)) );
            ESP_LOGI(TAG, "RVD_DATA:");
            for (int i=0; i<33; i++) {
                printf("%02x ", rvd_data[i]);
            }
            printf("\n");
        }

        // 断开当前WiFi连接
        ESP_ERROR_CHECK( esp_wifi_disconnect() );
        // 设置新的WiFi配置
        ESP_ERROR_CHECK( esp_wifi_set_config(WIFI_IF_STA, &wifi_config) );
        // 连接新的WiFi网络
        esp_wifi_connect();
    } 
    // 智能配网发送确认完成事件
    else if (event_base == SC_EVENT && event_id == SC_EVENT_SEND_ACK_DONE) {
        // 设置配网完成状态位
        xEventGroupSetBits(this_->event_group_, ESPTOUCH_DONE_BIT);
    }
}

/**
 * 初始化WiFi功能
 * 该函数完成WiFi相关的初始化工作，包括:
 * 1. 网络接口初始化
 * 2. 事件组创建
 * 3. 事件循环创建
 * 4. WiFi站点模式配置
 * 5. 注册事件处理程序
 * 6. 启动WiFi
 */
void SmartConfig::Start()
{
    // 创建WiFi事件组，用于同步WiFi操作
    if (is_running_) {
        return;
    }
    is_running_ = true;
    // 创建默认WiFi站点网络接口
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);

    // 使用默认配置初始化WiFi
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );

    // 注册WiFi事件处理程序
    ESP_ERROR_CHECK( esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &SmartConfig::EventHandler, this) );
    // 注册IP事件处理程序
    ESP_ERROR_CHECK( esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &SmartConfig::EventHandler, this) );
    // 注册智能配网事件处理程序
    ESP_ERROR_CHECK( esp_event_handler_register(SC_EVENT, ESP_EVENT_ANY_ID, &SmartConfig::EventHandler, this) );

    // 设置WiFi工作模式为站点模式
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    // 启动WiFi
    ESP_ERROR_CHECK( esp_wifi_start() );
}

/**
 * 智能配网任务函数
 * 该函数实现ESP32的智能配网功能，包括:
 * 1. 设置配网类型为ESPTOUCH_AIRKISS
 * 2. 启动智能配网
 * 3. 等待配网完成或WiFi连接成功
 * 
 * @param parm 任务参数(未使用)
 */
void SmartConfig::StartSmartConfigTask()
{
    // 定义事件位变量，用于接收事件组的状态
    xTaskCreate([](void* arg) {
        auto* this_ = static_cast<SmartConfig*>(arg);
        
        // 设置智能配网类型为ESPTOUCH_AIRKISS
        ESP_ERROR_CHECK( esp_smartconfig_set_type(SC_TYPE_ESPTOUCH_AIRKISS) );
        
        // 使用默认配置初始化智能配网配置结构体
        smartconfig_start_config_t cfg = SMARTCONFIG_START_CONFIG_DEFAULT();
        
        // 启动智能配网
        ESP_ERROR_CHECK( esp_smartconfig_start(&cfg) );
        
        // 进入无限循环，等待配网结果
        while (this_->is_running_) {
            // 等待WiFi连接成功或配网完成事件
            EventBits_t uxBits = xEventGroupWaitBits(this_->event_group_, 
                                                    CONNECTED_BIT | ESPTOUCH_DONE_BIT, 
                                                    true, false, portMAX_DELAY);
        
            // 检查WiFi连接状态
            if(uxBits & CONNECTED_BIT) {
                ESP_LOGI(TAG, "WiFi Connected to ap");
                if (this_->on_connected_) {
                    this_->on_connected_();
                }
                // 调用ssid_manager 保存ssid和password
                auto& ssid_manager = SsidManager::GetInstance();
                ssid_manager.AddSsid(this_->ssid_, this_->password_);
            }
            
            // 检查配网完成状态
            if(uxBits & ESPTOUCH_DONE_BIT) {
                ESP_LOGI(TAG, "smartconfig over");
                // 停止智能配网
                esp_smartconfig_stop();
                this_->is_running_ = false;
                if (this_->on_config_done_) {
                    this_->on_config_done_();
                }
                vTaskDelete(NULL);
            }
        }
    }, "SmartConfigTask", 4096, this, 3, NULL);
}

#include "wifi_board.h"
#include "audio_codecs/es8311_audio_codec.h"
#include "display/display.h"
#include "application.h"
#include "button.h"
#include "config.h"
#include "iot/thing_manager.h"
#include "led/single_led.h"

#include <wifi_station.h>
#include <esp_log.h>
#include <driver/i2c_master.h>
#include "sensors/mma8452q.h"
#include "driver/gpio.h"


#define TAG "MelontalkMagicBox"

class MelontalkMagicBox : public WifiBoard {
private:
    i2c_master_bus_handle_t codec_i2c_bus_;
    Button boot_button_;
    Display* display_;
    std::unique_ptr<MMA8452Q> accelerometer_;

    void InitializeCodecI2c() {
        // Initialize I2C peripheral
        i2c_master_bus_config_t i2c_bus_cfg = {
            .i2c_port = I2C_NUM_0,
            .sda_io_num = AUDIO_CODEC_I2C_SDA_PIN,
            .scl_io_num = AUDIO_CODEC_I2C_SCL_PIN,
            .clk_source = I2C_CLK_SRC_DEFAULT,
            .glitch_ignore_cnt = 7,
            .intr_priority = 0,
            .trans_queue_depth = 0,
            .flags = {
                .enable_internal_pullup = 1,
            },
        };
        ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_bus_cfg, &codec_i2c_bus_));
    }
    void InitializeButtons() {
        boot_button_.OnClick([this]() {
            auto& app = Application::GetInstance();
            if (app.GetDeviceState() == kDeviceStateStarting && !WifiStation::GetInstance().IsConnected()) {
                ResetWifiConfiguration();
            }
            app.ToggleChatState();
        });
    }
    void InitializeAccelerometer() {
        accelerometer_ = std::make_unique<MMA8452Q>(codec_i2c_bus_, ACC_GPIO_INT1);
        if (!accelerometer_->Initialize()) {
            ESP_LOGE(TAG, "Failed to initialize accelerometer");
            return;
        }

        accelerometer_->OnShake([]() {
            auto& app = Application::GetInstance();
            std::string wake_word="喵喵同学";
            app.WakeWordInvoke(wake_word);  // 使用现有的唤醒词机制来处理摇一摇
        });
    }
    void InitializeDisplay() {
        display_ = new NoDisplay();
    }

    // 物联网初始化，添加对 AI 可见设备
    void InitializeIot() {
        auto& thing_manager = iot::ThingManager::GetInstance();
        thing_manager.AddThing(iot::CreateThing("Speaker")); 
    }

public:
    MelontalkMagicBox() : boot_button_(BOOT_BUTTON_GPIO) {  
        InitializeCodecI2c();
        InitializeDisplay();
        InitializeAccelerometer();
        InitializeButtons();
        InitializeIot();
       
    }

    virtual Led* GetLed() override {
        static SingleLed led(BUILTIN_LED_GPIO);
        return &led;
    }

    virtual Display* GetDisplay() override {
        return display_;
    }
    

    virtual AudioCodec* GetAudioCodec() override {
        static Es8311AudioCodec audio_codec(codec_i2c_bus_, I2C_NUM_0, AUDIO_INPUT_SAMPLE_RATE, AUDIO_OUTPUT_SAMPLE_RATE,
            AUDIO_I2S_GPIO_MCLK, AUDIO_I2S_GPIO_BCLK, AUDIO_I2S_GPIO_WS, AUDIO_I2S_GPIO_DOUT, AUDIO_I2S_GPIO_DIN,
            AUDIO_CODEC_PA_PIN, AUDIO_CODEC_ES8311_ADDR);
        return &audio_codec;
    }
};

DECLARE_BOARD(MelontalkMagicBox);

#include <driver/i2c_master.h>
#include <driver/spi_common.h>
#include <esp_lcd_panel_vendor.h>
#include <esp_log.h>
#include <wifi_station.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <dirent.h>

#include "application.h"
#include "audio_codecs/es8311_audio_codec.h"
#include "button.h"
#include "config.h"
#include "display/lcd_display.h"
#include "esp_lcd_jd9853.h"
#include "font_awesome_symbols.h"
#include "iot/thing_manager.h"
#include "wifi_board.h"
#include "headphone_detector.h"
#include "power_manager.h"
#include "driver/sdmmc_host.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "power_save_timer.h"
#include "settings.h"

#define TAG "AiKoderS3LcdBoard"

// LV_FONT_DECLARE(font_puhui_20_4);
// LV_FONT_DECLARE(font_awesome_20_4);
LV_FONT_DECLARE(font_puhui_16_4);      // 中文+葡萄牙语字体
LV_FONT_DECLARE(font_awesome_16_4);    // 图标字体
LV_FONT_DECLARE(font_thai_16_4);       // 泰语字体
LV_FONT_DECLARE(font_arabic_16_4);     // 阿拉伯语字体

class AiKoderS3LcdBoard : public WifiBoard
{
private:
    i2c_master_bus_handle_t i2c_bus_;
    Button boot_button_;
    LcdDisplay *display_;
    HeadphoneDetector headphone_detector_;
    PowerManager *power_manager_;
    esp_timer_handle_t timer_handle_;
    bool press_to_talk_enabled_ = false;
    PowerSaveTimer* power_save_timer_;

    void InitializePowerSaveTimer() {
        power_save_timer_ = new PowerSaveTimer(160, 60);
        power_save_timer_->OnEnterSleepMode([this]() {
            ESP_LOGI(TAG, "Enabling sleep mode");
            auto display = GetDisplay();
            display->SetChatMessage("system", "");
            display->SetEmotion("sleepy");
            
            auto codec = GetAudioCodec();
            codec->EnableInput(false);
        });
        power_save_timer_->OnExitSleepMode([this]() {
            auto codec = GetAudioCodec();
            codec->EnableInput(true);
            
            auto display = GetDisplay();
            display->SetChatMessage("system", "");
            display->SetEmotion("neutral");
        });
        power_save_timer_->SetEnabled(true);
    }

    void InitializeAutoListen() {
        esp_timer_create_args_t timer_args = {
            .callback = [](void* arg) {
                // PowerManager* self = static_cast<PowerManager*>(arg);
                // self->CheckBatteryStatus();
                printf("detect listen...\n");

                auto& app = Application::GetInstance();
                if (app.GetDeviceState() == kDeviceStateIdle) {
                    app.ToggleChatState();
                }

            },
            .arg = this,
            .dispatch_method = ESP_TIMER_TASK,
            .name = "battery_check_timer",
            .skip_unhandled_events = true,
        };
        ESP_ERROR_CHECK(esp_timer_create(&timer_args, &timer_handle_));
        ESP_ERROR_CHECK(esp_timer_start_periodic(timer_handle_, 3000000));
    }

    void InitializeI2c()
    {
        // Initialize I2C peripheral
        i2c_master_bus_config_t i2c_bus_cfg = {
            .i2c_port = (i2c_port_t)1,
            .sda_io_num = AUDIO_CODEC_I2C_SDA_PIN,
            .scl_io_num = AUDIO_CODEC_I2C_SCL_PIN,
            .clk_source = I2C_CLK_SRC_DEFAULT,
            .glitch_ignore_cnt = 7,
            .intr_priority = 0,
            .trans_queue_depth = 0,
            .flags =
                {
                    .enable_internal_pullup = 1,
                },
        };
        ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_bus_cfg, &i2c_bus_));
    }

    void InitializeSpi()
    {
        spi_bus_config_t buscfg = {};
        buscfg.mosi_io_num = DISPLAY_SPI_MOSI_PIN;
        buscfg.miso_io_num = DISPLAY_SPI_MISO_PIN;
        buscfg.sclk_io_num = DISPLAY_SPI_SCLK_PIN;
        buscfg.quadwp_io_num = GPIO_NUM_NC;
        buscfg.quadhd_io_num = GPIO_NUM_NC;
        buscfg.max_transfer_sz = DISPLAY_WIDTH * 80 * sizeof(uint16_t);
        ESP_ERROR_CHECK(spi_bus_initialize(SPI3_HOST, &buscfg, SPI_DMA_CH_AUTO));
        printf("InitializeSpi OK.\n");
    }

    void InitializeButtons()
    {
        boot_button_.OnClick([this]() {
        auto& app = Application::GetInstance();
            if (app.GetDeviceState() == kDeviceStateStarting &&
                !WifiStation::GetInstance().IsConnected()) {
                ResetWifiConfiguration();
            }
            //   app.ToggleChatState(); 
            if (!press_to_talk_enabled_) {
                app.ToggleChatState();
            }
        });

        boot_button_.OnPressDown([this]() {
            // power_save_timer_->WakeUp();
            if (press_to_talk_enabled_) {
                Application::GetInstance().StartListening();
            }
        });

        boot_button_.OnPressUp([this]() {
            if (press_to_talk_enabled_) {
                Application::GetInstance().StopListening();
            }
        });
    }

    void InitializeJd9853Display()
    {
        esp_lcd_panel_io_handle_t panel_io = nullptr;
        esp_lcd_panel_handle_t panel = nullptr;

        // 液晶屏控制IO初始化
        ESP_LOGD(TAG, "Install panel IO");
        ESP_LOGI(TAG, "Install panel IO");
        esp_lcd_panel_io_spi_config_t io_config = {};
        io_config.cs_gpio_num = DISPLAY_SPI_CS_PIN;
        io_config.dc_gpio_num = DISPLAY_SPI_DC_PIN;
        io_config.spi_mode = 0;
        io_config.pclk_hz = 80 * 1000 * 1000;
        io_config.trans_queue_depth = 10;
        io_config.lcd_cmd_bits = 8;
        io_config.lcd_param_bits = 8;
        ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi(SPI3_HOST, &io_config, &panel_io));

        // 初始化液晶屏驱动芯片
        ESP_LOGD(TAG, "Install LCD driver");
        ESP_LOGI(TAG, "Install LCD driver");
        esp_lcd_panel_dev_config_t panel_config = {};
        panel_config.reset_gpio_num = DISPLAY_SPI_RST_PIN;
        // panel_config.flags.reset_active_high = 1,
        panel_config.rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB;
        panel_config.bits_per_pixel = 16;
        // panel_config.vendor_config = (void *)&vendor_config;
        // ESP_ERROR_CHECK(esp_lcd_new_panel_nv3030b(panel_io, &panel_config, &panel));
        ESP_ERROR_CHECK(esp_lcd_new_panel_jd9853(panel_io, &panel_config, &panel));

        esp_lcd_panel_reset(panel);
        esp_lcd_panel_init(panel);
        esp_lcd_panel_invert_color(panel, DISPLAY_BACKLIGHT_OUTPUT_INVERT);

        // #if CONFIG_EXAMPLE_DISPLAY_ROTATION == 90
        //         ESP_ERROR_CHECK(esp_lcd_panel_set_gap(panel_handle, 0, 0));
        //         ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, true, false));
        //         ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, true));
        // #elif CONFIG_EXAMPLE_DISPLAY_ROTATION == 180
        //         ESP_ERROR_CHECK(esp_lcd_panel_set_gap(panel_handle, 34, 0));
        //         ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, true, true));
        //         ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, false));
        // #elif CONFIG_EXAMPLE_DISPLAY_ROTATION == 270
        //         ESP_ERROR_CHECK(esp_lcd_panel_set_gap(panel_handle, 24, 0));
        //         ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, false, true));
        //         ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, true));
        // #else
        //         ESP_ERROR_CHECK(esp_lcd_panel_set_gap(panel_handle, 34, 0));
        //         ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, false, false));
        // #endif

#if CONFIG_DISPLAY_ROTATION_90
        ESP_ERROR_CHECK(esp_lcd_panel_set_gap(panel, 0, 0));
#elif CONFIG_DISPLAY_ROTATION_180
        ESP_ERROR_CHECK(esp_lcd_panel_set_gap(panel, 0, 24));
#elif CONFIG_DISPLAY_ROTATION_270
        ESP_ERROR_CHECK(esp_lcd_panel_set_gap(panel, 24, 0));
#else
        ESP_ERROR_CHECK(esp_lcd_panel_set_gap(panel, 0, 0));
#endif
        esp_lcd_panel_swap_xy(panel, DISPLAY_SWAP_XY);
        esp_lcd_panel_mirror(panel, DISPLAY_MIRROR_X, DISPLAY_MIRROR_Y);

        esp_lcd_panel_disp_on_off(panel, true);
        
        // 设置字体回退链：中文+葡萄牙语 -> 泰语 -> 阿拉伯语
        font_puhui_16_4.fallback = &font_thai_16_4;
        font_thai_16_4.fallback = &font_arabic_16_4;
        
        display_ = new SpiLcdDisplay(
            panel_io, panel, DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_OFFSET_X,
            DISPLAY_OFFSET_Y, DISPLAY_MIRROR_X, DISPLAY_MIRROR_Y, DISPLAY_SWAP_XY,
            {
                .text_font = &font_puhui_16_4,    // 主字体：中文+葡萄牙语，自动回退到泰语和阿拉伯语
                .icon_font = &font_awesome_16_4,
#if CONFIG_USE_WECHAT_MESSAGE_STYLE
                .emoji_font = font_emoji_32_init(),
#else
                .emoji_font = font_emoji_64_init(),
#endif
            });
    }

    // 物联网初始化，添加对 AI 可见设备
    void InitializeIot()
    {
        Settings settings("vendor");
        press_to_talk_enabled_ = settings.GetInt("press_to_talk", 0) != 0;

        auto &thing_manager = iot::ThingManager::GetInstance();
        thing_manager.AddThing(iot::CreateThing("Speaker"));
        thing_manager.AddThing(iot::CreateThing("Screen"));
        thing_manager.AddThing(iot::CreateThing("Battery"));
        thing_manager.AddThing(iot::CreateThing("PressToTalk"));
    }

    void InitializePowerManager()
    {
        power_manager_ = new PowerManager(BATTERY_CHARGING_DETECT_PIN, BATTERY_CHARGED_DETECT_PIN);
        power_manager_->OnChargingStatusChanged([this](bool is_charging)
                                                {
                                                    // if (is_charging) {
                                                    //     power_save_timer_->SetEnabled(false);
                                                    // } else {
                                                    //     power_save_timer_->SetEnabled(true);
                                                    // }
                                                });
        power_manager_->OnLowBatteryStatusChanged([this](bool is_low_battery)
                                                {
                                                    if (is_low_battery)
                                                    {
                                                        GetBacklight()->SetBrightness(10);
                                                    }
                                                    else
                                                    {
                                                        GetBacklight()->RestoreBrightness();
                                                    }
                                                });
    }

    void InitializeSdcard() {
        gpio_set_direction(TF_CARD_SD_DETECT_PIN, GPIO_MODE_INPUT);
        gpio_set_pull_mode(TF_CARD_SD_DETECT_PIN, GPIO_PULLUP_ONLY);

        esp_err_t ret = ESP_OK;
        sdmmc_card_t *card;
        const char *mount_point = "/sdcard";

        esp_vfs_fat_sdmmc_mount_config_t mount_config = {
            .format_if_mount_failed = true,
            .max_files = 5,
            .allocation_unit_size = 16 * 1024,
        };
        // sdmmc_card_t *card;
        printf("Initializing SD card\n");

        sdmmc_host_t host = SDMMC_HOST_DEFAULT();

        sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
        slot_config.width = 4;
        slot_config.clk = TF_CARD_SD_CLK_PIN;
        slot_config.cmd = TF_CARD_SD_CMD_PIN;
        slot_config.d0 = TF_CARD_SD_DATA0_PIN;
        slot_config.d1 = TF_CARD_SD_DATA1_PIN;
        slot_config.d2 = TF_CARD_SD_DATA2_PIN;
        slot_config.d3 = TF_CARD_SD_DATA3_PIN;
        slot_config.flags |= SDMMC_SLOT_FLAG_INTERNAL_PULLUP;

        printf("Mounting filesystem\n");
        ret = esp_vfs_fat_sdmmc_mount(mount_point, &host, &slot_config, &mount_config,
                                    &card);

        if (ret != ESP_OK)
        {
            if (ret == ESP_FAIL)
            {
                ESP_LOGE(TAG, "Failed to mount filesystem. "
                            "If you want the card to be formatted, set the "
                            "EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.");
            }
            else
            {
                ESP_LOGE(TAG,
                        "Failed to initialize the card (%s). "
                        "Make sure SD card lines have pull-up resistors in place.",
                        esp_err_to_name(ret));
            }
        }
        ESP_LOGI(TAG, "Filesystem mounted");

        sdmmc_card_print_info(stdout, card);
    }

public:
    AiKoderS3LcdBoard() : boot_button_(BOOT_BUTTON_GPIO),
                          headphone_detector_(HEADPHONE_DETECT_PIN, AUDIO_CODEC_PA_PIN)
    {
        InitializeI2c();
        InitializeSpi();
        InitializeJd9853Display();
        InitializeButtons();
        // InitializePowerSaveTimer();
        InitializeIot();
        GetBacklight()->RestoreBrightness();
        // InitializeAutoListen();
        // InitializeSdcard();

        esp_err_t err = headphone_detector_.Initialize();
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "Failed to initialize Headphone Detector: %s", esp_err_to_name(err));
            // Handle the error appropriately - maybe disable audio features?
        }
        else
        {
            ESP_LOGI(TAG, "Headphone Detector initialized.");
            headphone_detector_.setCallback(
                // Capture 'this' if you need to access AiKoderS3LcdBoard members
                [this](HeadphoneState state)
                {
                    // --- This is the user-defined action when state changes ---
                    // In this lambda, you define what happens when headphones are plugged/unplugged

                    // Option 1: Use the default PA control action provided by the class
                    // headphone_detector_.setDefaultPaAction(state);

                    // Option 2: Implement custom logic here
                    if (state == HeadphoneState::PLUGGED_IN)
                    {
                        ESP_LOGI(TAG, "AiKoderS3LcdBoard Callback: Headphones plugged in. Doing custom actions.");
                        // Example: Disable speaker PA pin directly
                        gpio_set_level(AUDIO_CODEC_PA_PIN, 0);
                        // TODO: Configure ES8311 codec for headphone output
                    }
                    else
                    {
                        ESP_LOGI(TAG, "AiKoderS3LcdBoard Callback: Headphones unplugged. Doing custom actions.");
                        // Example: Enable speaker PA pin directly
                        gpio_set_level(AUDIO_CODEC_PA_PIN, 1);
                        // TODO: Configure ES8311 codec for speaker output
                    }

                    // TODO: Potentially inform the audio system (e.g. GetAudioCodec())
                    // about the change so it can reconfigure the codec if needed.
                    // This is a more advanced step depending on your audio framework.
                    // You might need to pass a pointer to the audio codec instance
                    // or have the audio system listen for a different event triggered here.

                    // --- End of user-defined action ---
                });
            ESP_LOGI(TAG, "Headphone Detector callback set.");
        }

        InitializePowerManager();
    }

    virtual AudioCodec *GetAudioCodec() override
    {
        static Es8311AudioCodec audio_codec(
            i2c_bus_,
            I2C_NUM_0,
            AUDIO_INPUT_SAMPLE_RATE,
            AUDIO_OUTPUT_SAMPLE_RATE,
            AUDIO_I2S_GPIO_MCLK,
            AUDIO_I2S_GPIO_BCLK,
            AUDIO_I2S_GPIO_WS,
            AUDIO_I2S_GPIO_DOUT,
            AUDIO_I2S_GPIO_DIN,
            AUDIO_CODEC_PA_PIN,
            AUDIO_CODEC_ES8311_ADDR,
            true);
        return &audio_codec;
    }

    virtual Display *GetDisplay() override { return display_; }

    virtual Backlight *GetBacklight() override
    {
        static PwmBacklight backlight(DISPLAY_BACKLIGHT_PIN,
                                      DISPLAY_BACKLIGHT_OUTPUT_INVERT);
        return &backlight;
    }

    // old board needs it
    virtual bool GetBatteryLevel(int &level, bool &charging, bool &discharging) override
    {
        static bool last_discharging = false;
        charging = power_manager_->IsCharging();
        discharging = power_manager_->IsDischarging();
        if (discharging != last_discharging)
        {
            last_discharging = discharging;
        }
        level = power_manager_->GetBatteryLevel();
        return true;
    }

    void Headphone_detector_set(void)
    {
        if (headphone_detector_.getCurrentState() == HeadphoneState::PLUGGED_IN)
        {
            ESP_LOGI(TAG, "Set PA PIN -> 0");
            gpio_set_level(AUDIO_CODEC_PA_PIN, 0);
        }
        else
        {
            ESP_LOGI(TAG, "Set PA PIN -> 1");
            gpio_set_level(AUDIO_CODEC_PA_PIN, 1);
        }
    }

    void SetPressToTalkEnabled(bool enabled) {
        press_to_talk_enabled_ = enabled;

        Settings settings("vendor", true);
        settings.SetInt("press_to_talk", enabled ? 1 : 0);
        ESP_LOGI(TAG, "Press to talk enabled: %d", enabled);
    }

    bool IsPressToTalkEnabled() {
        return press_to_talk_enabled_;
    }
};

DECLARE_BOARD(AiKoderS3LcdBoard);

namespace iot {

class PressToTalk : public Thing {
public:
    PressToTalk() : Thing("PressToTalk", "控制对话模式，一种是长按对话，一种是单击后连续对话。") {
        // 定义设备的属性
        properties_.AddBooleanProperty("enabled", "true 表示长按说话模式，false 表示单击说话模式", []() -> bool {
            auto board = static_cast<AiKoderS3LcdBoard*>(&Board::GetInstance());
            return board->IsPressToTalkEnabled();
        });

        // 定义设备可以被远程执行的指令
        methods_.AddMethod("SetEnabled", "启用或禁用长按说话模式，调用前需要经过用户确认", ParameterList({
            Parameter("enabled", "true 表示长按说话模式，false 表示单击说话模式", kValueTypeBoolean, true)
        }), [](const ParameterList& parameters) {
            bool enabled = parameters["enabled"].boolean();
            auto board = static_cast<AiKoderS3LcdBoard*>(&Board::GetInstance());
            board->SetPressToTalkEnabled(enabled);
        });
    }
};

} // namespace iot

DECLARE_THING(PressToTalk);
#include "mma8452q.h"
#include <esp_log.h>

#define TAG "MMA8452Q"

// MMA8452Q寄存器地址定义
#define REG_STATUS          0x00  // 状态寄存器
#define REG_OUT_X_MSB       0x01  // X轴数据高字节
#define REG_OUT_X_LSB       0x02  // X轴数据低字节
#define REG_OUT_Y_MSB       0x03  // Y轴数据高字节
#define REG_OUT_Y_LSB       0x04  // Y轴数据低字节
#define REG_OUT_Z_MSB       0x05  // Z轴数据高字节
#define REG_OUT_Z_LSB       0x06  // Z轴数据低字节
#define REG_SYSMOD          0x0B  // 系统模式寄存器
#define REG_INT_SOURCE      0x0C  // 中断源寄存器
#define REG_WHO_AM_I        0x0D  // 设备ID寄存器
#define REG_XYZ_DATA_CFG    0x0E  // XYZ数据配置寄存器
#define REG_CTRL_REG1       0x2A  // 控制寄存器1
#define REG_CTRL_REG2       0x2B  // 控制寄存器2
#define REG_CTRL_REG3       0x2C  // 控制寄存器3
#define REG_CTRL_REG4       0x2D  // 控制寄存器4
#define REG_CTRL_REG5       0x2E  // 控制寄存器5

// 中断源定义
#define INT_SRC_DRDY        0x01  // 数据就绪中断
#define INT_SRC_FF_MT       0x04  // 自由落体/运动检测中断
#define INT_SRC_PULSE       0x08  // 脉冲检测中断
#define INT_SRC_LNDPRT      0x10  // 方向变化中断
#define INT_SRC_TRANS       0x20  // 转置中断
#define INT_SRC_ASLP        0x80  // 自动休眠中断
// 添加缺失的寄存器地址定义
#define MMA845X_REG_FF_MT_CFG    0x15  // 自由落体/运动检测配置寄存器
#define MMA845X_REG_FF_MT_THS    0x17  // 自由落体/运动检测阈值寄存器
#define MMA845X_REG_FF_MT_COUNT  0x18  // 自由落体/运动检测去抖动计数器
#define REG_OUT_FF_MT_SRC 0x16 // 自由落体/运动检测源寄存器

// 设备ID
#define MMA8452Q_ID         0x2A  // WHO_AM_I寄存器的值

MMA8452Q::MMA8452Q(i2c_master_bus_handle_t i2c_bus, gpio_num_t int1_pin)
    : I2cDevice(i2c_bus, I2C_ADDR), int1_pin_(int1_pin),
      shake_callback_(nullptr), update_task_handle_(nullptr), gpio_evt_queue(nullptr) {
}

MMA8452Q::~MMA8452Q() {
    // 停止更新任务
    if (update_task_handle_ != nullptr) {
        vTaskDelete(update_task_handle_);
        update_task_handle_ = nullptr;
    }
    
    // 移除GPIO中断处理程序
    if (int1_pin_ != GPIO_NUM_NC) {
        gpio_isr_handler_remove(int1_pin_);
    }
    
    // 禁用传感器
    uint8_t ctrl_reg1 = ReadReg(REG_CTRL_REG1);
    WriteReg(REG_CTRL_REG1, ctrl_reg1 & ~0x01);  // 清除激活位
}

bool MMA8452Q::Initialize() {
    ESP_LOGI(TAG, "Initializing MMA8452Q accelerometer");
    
    // 检查设备ID
    uint8_t who_am_i = ReadReg(REG_WHO_AM_I);
    if (who_am_i != MMA8452Q_ID) {
        ESP_LOGE(TAG, "Wrong device ID: expected 0x%02x, got 0x%02x", MMA8452Q_ID, who_am_i);
        return false;
    }
     
    // 配置GPIO中断引脚
    if (int1_pin_ != GPIO_NUM_NC) {
        gpio_evt_queue = xQueueCreate(10, sizeof(uint8_t));
        
        // 安装GPIO ISR服务
        ESP_ERROR_CHECK(gpio_install_isr_service(0));

		gpio_config_t io_conf = {};
        io_conf.intr_type = GPIO_INTR_ANYEDGE;  // 任意边沿触发
        io_conf.pin_bit_mask = (1ULL << int1_pin_);
        io_conf.mode = GPIO_MODE_INPUT;
        io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
        ESP_ERROR_CHECK(gpio_config(&io_conf));
        
        // 添加中断处理程序
        ESP_ERROR_CHECK(gpio_isr_handler_add(int1_pin_, HandleInterrupt, this));
        
        ESP_LOGI(TAG, "Interrupt configured on GPIO %d", int1_pin_);
    }
    
    // 进入待机模式以配置传感器
    WriteReg(REG_CTRL_REG1, 0x00);  // 清除激活位，进入待机模式
    
    // 配置数据格式 - 设置为±2g范围
    WriteReg(REG_XYZ_DATA_CFG, 0x00);  // 00 = ±2g, 01 = ±4g, 10 = ±8g

    // 配置事件
    // struct mma845x_reg_ff_mt_cfg
    // {
    //     uint8_t unused:3; // FF_MT_CFG<2:0> unused
    //     uint8_t XEFE  :1; // FF_MT_CFG<3>   Event flag enable on X event
    //     uint8_t YEFE  :1; // FF_MT_CFG<4>   Event flag enable on Y event
    //     uint8_t ZEFE  :1; // FF_MT_CFG<5>   Event flag enable on Z event
    //     uint8_t OAE   :1; // FF_MT_CFG<6>   Motion detect / freefall detect selection
    //     uint8_t ELE   :1; // FF_MT_CFG<6>   Event latch enable
    // };
    WriteReg(MMA845X_REG_FF_MT_CFG, 0xD8);
    // struct mma845x_reg_ff_mt_ths
    // {
    //     uint8_t THS   :7; // FF_MT_CFG<6:0> Freefall/motion threshold
    //     uint8_t DBCNTM:1; // FF_MT_CFG<7>   Debounce counter mode selection
    // };
    WriteReg(MMA845X_REG_FF_MT_THS, 0x14);
    // event_config.debounce_cnt = 5; // 100 ms at ODR=50Hz in normal oversampling mode
    WriteReg(MMA845X_REG_FF_MT_COUNT, 0x08);
    // struct mma845x_reg_ctrl3
    // {
    //     uint8_t PP_OD      :1; // CTRL3<0>   Push-pull/open drain interrupt pad
    //     uint8_t IPOL       :1; // CTRL3<1>   Interrupt polarity
    //     uint8_t unused     :1; // CTRL3<2>   unused
    //     uint8_t WAKE_FF_MT :1; // CTRL3<3>   Freefall/motion function wake up
    //     uint8_t WAKE_PULSE :1; // CTRL3<4>   Pulse function wake up
    //     uint8_t WAKE_LNDPRT:1; // CTRL3<5>   Orientatoin function wake up
    //     uint8_t WAKE_TRANS :1; // CTRL3<6>   Transient function wake up
    //     uint8_t FIFO_GATE  :1; // CTRL3<7>   FIFO gate handling in state transition

    // };
    WriteReg(REG_CTRL_REG3, 0x08);
    // 配置中断 - 使用INT1引脚进行震动检测
    WriteReg(REG_CTRL_REG4, 0x04);  // 启用自由落体/运动检测中断
    WriteReg(REG_CTRL_REG5, 0x04);  // 将自由落体/运动检测中断路由到INT1引脚
    
    // 配置控制寄存器2 - 高通滤波用于运动检测
    WriteReg(REG_CTRL_REG2, 0x10);  // 启用高通滤波用于运动检测
    
    // 配置控制寄存器1 - 设置数据速率和激活传感器
    WriteReg(REG_CTRL_REG1, 0x01 | (0x04 << 3));  // 激活传感器，ODR=100Hz，低噪声模式关闭
    
   
    // 创建更新任务
    // xTaskCreate(UpdateTask, "mma8452q_task", 4096, this, 3, &update_task_handle_);

     xTaskCreate(user_task_interrupt, "user_task_interrupt", 4096, this, 2, NULL);
    
    ESP_LOGI(TAG, "MMA8452Q initialized successfully");
    return true;
}

void MMA8452Q::OnShake(std::function<void()> callback) {
    shake_callback_ = callback;
}


void IRAM_ATTR MMA8452Q::HandleInterrupt(void* arg) {
    MMA8452Q* sensor = static_cast<MMA8452Q*>(arg);
    
    // 如果使用队列，则发送事件
    if (sensor->gpio_evt_queue) {
        uint8_t gpio = sensor->int1_pin_;
        xQueueSendFromISR(sensor->gpio_evt_queue, &gpio, NULL);
    }
}



void MMA8452Q::ProcessInterrupt() {
    // 读取中断源寄存器以确定中断类型
    uint8_t int_source = ReadReg(REG_INT_SOURCE);
    ESP_LOGI(TAG, "Interrupt detected!");
    // 检查是否为运动检测中断
    if (int_source & INT_SRC_FF_MT) {
        ESP_LOGI(TAG, "Motion detected!");
        // 读取自由落体/运动检测源寄存器
        uint8_t ff_mt_src = ReadReg(REG_OUT_FF_MT_SRC);
        ESP_LOGI(TAG, "Freefall/Motion Source: 0x%02x", ff_mt_src);
        // 如果设置了回调函数，则调用它
        if (shake_callback_) {
            shake_callback_();
        }
    }
    
}

void MMA8452Q::UpdateTask(void* arg) {
    MMA8452Q* sensor = static_cast<MMA8452Q*>(arg);
    
    while (true) {
         // 读取三轴加速度数据
         int16_t x = (sensor->ReadReg(REG_OUT_X_MSB) << 8) | sensor->ReadReg(REG_OUT_X_LSB);
         int16_t y = (sensor->ReadReg(REG_OUT_Y_MSB) << 8) | sensor->ReadReg(REG_OUT_Y_LSB);
         int16_t z = (sensor->ReadReg(REG_OUT_Z_MSB) << 8) | sensor->ReadReg(REG_OUT_Z_LSB);
         
         // 将原始数据转换为实际加速度值（单位：g）
         float x_g = x / 4096.0f;  // 12位分辨率，±2g量程
         float y_g = y / 4096.0f;
         float z_g = z / 4096.0f;
         
         // 打印三轴加速度值
         ESP_LOGI(TAG, "Acceleration: X=%.2fg, Y=%.2fg, Z=%.2fg", x_g, y_g, z_g);
         

        
        // 短暂延时，避免占用过多CPU资源
        vTaskDelay(pdMS_TO_TICKS(150));
    }
}

void MMA8452Q::user_task_interrupt(void* arg) {
    // 正确获取 sensor 指针
    MMA8452Q* sensor = static_cast<MMA8452Q*>(arg);
    uint8_t gpio_num;
    
    // 确保 sensor 不为 NULL 且 gpio_evt_queue 已初始化
    if (sensor && sensor->gpio_evt_queue) {
        while (true) {
            if (xQueueReceive(sensor->gpio_evt_queue, &gpio_num, portMAX_DELAY) == pdPASS) {
                sensor->ProcessInterrupt();
            }
            // 短暂延时，避免占用过多CPU资源
            vTaskDelay(pdMS_TO_TICKS(100));
        }
    } else {
        // 如果 sensor 为 NULL 或队列未初始化，记录错误并删除任务
        ESP_LOGE(TAG, "Invalid sensor pointer or queue in interrupt task");
        vTaskDelete(NULL);
    }
}
# 多语言字体支持指南

## 概述

本项目现在支持以下语言的字体显示：
- ✅ **中文** (已支持)
- ✅ **英文** (已支持) 
- ✅ **葡萄牙语** (新增)
- ✅ **泰语** (新增，需额外字体文件)
- ✅ **阿拉伯语** (新增，需额外字体文件)

## 字体支持情况

### AlibabaPuHuiTi-3-55-Regular.ttf
- ✅ 中文字符
- ✅ 英文字符
- ✅ 葡萄牙语字符 (重音符号等)
- ❌ 泰语字符
- ❌ 阿拉伯语字符

### 需要额外下载的字体
1. **泰语**: NotoSansThai-Regular.ttf
   - 下载地址: https://fonts.google.com/noto/specimen/Noto+Sans+Thai
   
2. **阿拉伯语**: NotoSansArabic-Regular.ttf
   - 下载地址: https://fonts.google.com/noto/specimen/Noto+Sans+Arabic

## 使用步骤

### 1. 检测字体支持情况
```bash
cd main/fonts
python test_font_support.py
```

### 2. 下载所需字体文件
将下载的字体文件放入 `main/fonts/` 目录：
```
main/fonts/
├── AlibabaPuHuiTi-3-55-Regular.ttf  (已有)
├── NotoSansThai-Regular.ttf         (需下载)
└── NotoSansArabic-Regular.ttf       (需下载)
```

### 3. 生成字体文件

#### 方式A: 生成包含葡萄牙语的中文字体 (推荐)
```bash
cd main/fonts
python generate_fonts.py  # 生成所有尺寸的中文+葡萄牙语字体
```

#### 方式B: 生成独立的多语言字体
```bash
cd main/fonts
python generate_multilang_fonts.py  # 生成所有语言的字体
```

#### 方式C: 生成特定语言字体
```bash
# 只生成葡萄牙语字体
python multilang_font.py lvgl --font-size 14 --bpp 1 --lang portuguese

# 只生成泰语字体
python multilang_font.py lvgl --font-size 14 --bpp 1 --lang thai

# 只生成阿拉伯语字体
python multilang_font.py lvgl --font-size 14 --bpp 1 --lang arabic
```

## 在代码中使用

### 1. 包含头文件
```cpp
#include "multilang_fonts.h"
```

### 2. 声明字体 (已在头文件中声明)
```cpp
// 现有中文字体已包含葡萄牙语支持
LV_FONT_DECLARE(font_puhui_14_1);  // 适合OLED

// 独立语言字体
LV_FONT_DECLARE(font_thai_14_1);   // 泰语
LV_FONT_DECLARE(font_arabic_14_1); // 阿拉伯语
```

### 3. 使用字体回退机制

#### 方法A: 设置字体回退链
```cpp
// 在你的板子初始化代码中
void InitializeDisplay() {
    // 设置字体回退链：中文 -> 泰语 -> 阿拉伯语
    font_puhui_14_1.fallback = &font_thai_14_1;
    font_thai_14_1.fallback = &font_arabic_14_1;
    
    display_ = new OledDisplay(panel_io_, panel_, DISPLAY_WIDTH, DISPLAY_HEIGHT, 
        DISPLAY_MIRROR_X, DISPLAY_MIRROR_Y,
        {&font_puhui_14_1, &font_awesome_14_1});  // 主字体包含中文+葡萄牙语
}
```

#### 方法B: 根据语言动态切换字体
```cpp
class MultiLangDisplay {
private:
    const lv_font_t* GetFontForLanguage(const std::string& lang) {
        if (lang == "zh" || lang == "pt") {
            return &font_puhui_14_1;  // 中文+葡萄牙语
        } else if (lang == "th") {
            return &font_thai_14_1;   // 泰语
        } else if (lang == "ar") {
            return &font_arabic_14_1; // 阿拉伯语
        }
        return &font_puhui_14_1;  // 默认
    }

public:
    void SetLanguage(const std::string& lang) {
        current_font_ = GetFontForLanguage(lang);
        // 更新显示...
    }
};
```

## BPP (Bits Per Pixel) 选择建议

| 显示器类型 | 推荐BPP | 字体示例 | 说明 |
|------------|---------|----------|------|
| OLED (单色) | 1 bpp | `font_*_14_1` | 最小内存，无抗锯齿 |
| 彩色LCD | 4 bpp | `font_*_16_4` | 平衡质量和大小 |
| 高分辨率彩色 | 8 bpp | `font_*_20_8` | 最佳质量，需要时手动生成 |

## 文件大小估算

| 语言 | 字符数 | 1 bpp | 4 bpp | 说明 |
|------|--------|-------|-------|------|
| 葡萄牙语 | ~24 | +2KB | +8KB | 追加到中文字体 |
| 泰语 | ~128 | ~15KB | ~60KB | 独立字体文件 |
| 阿拉伯语 | ~256 | ~30KB | ~120KB | 独立字体文件 |

## 示例：bread-compact-wifi 板子适配

```cpp
// 在 compact_wifi_board.cc 中
#include "multilang_fonts.h"

class CompactWifiBoard : public WifiBoard {
    void InitializeSsd1306Display() {
        // ... existing code ...
        
        // 设置多语言字体支持
        font_puhui_14_1.fallback = &font_arabic_14_1;  // 如果中文字体没有字符，回退到阿拉伯语
        
        display_ = new OledDisplay(panel_io_, panel_, DISPLAY_WIDTH, DISPLAY_HEIGHT, 
            DISPLAY_MIRROR_X, DISPLAY_MIRROR_Y,
            {&font_puhui_14_1, &font_awesome_14_1});  // 主字体已包含中文+葡萄牙语
    }
};
```

## 故障排除

### 问题1: 字体生成失败
```bash
# 检查是否安装了 lv_font_conv
npm install -g lv_font_conv

# 检查字体文件是否存在
ls -la *.ttf
```

### 问题2: 字符显示为方块
- 确认字体文件包含所需字符
- 检查字体回退链是否正确设置
- 运行 `python test_font_support.py` 检测支持情况

### 问题3: 编译错误
- 确认已包含 `multilang_fonts.h`
- 检查字体文件是否已生成在 `src/` 目录
- 确认 CMakeLists.txt 包含了字体源文件

## 依赖

```bash
# Python 依赖
pip install fonttools

# Node.js 依赖
npm install -g lv_font_conv
``` 
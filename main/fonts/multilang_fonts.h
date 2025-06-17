#ifndef MULTILANG_FONTS_H
#define MULTILANG_FONTS_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

// 现有中文字体（已包含葡萄牙语字符）
LV_FONT_DECLARE(font_puhui_14_1);  // 中文+葡萄牙语，14px, 1bpp
LV_FONT_DECLARE(font_puhui_16_4);  // 中文+葡萄牙语，16px, 4bpp
LV_FONT_DECLARE(font_puhui_20_4);  // 中文+葡萄牙语，20px, 4bpp
LV_FONT_DECLARE(font_puhui_30_4);  // 中文+葡萄牙语，30px, 4bpp

// 葡萄牙语专用字体（如果需要单独生成）
LV_FONT_DECLARE(font_portuguese_14_1);
LV_FONT_DECLARE(font_portuguese_16_4);
LV_FONT_DECLARE(font_portuguese_20_4);

// 泰语字体
LV_FONT_DECLARE(font_thai_14_1);
LV_FONT_DECLARE(font_thai_16_4);

// 阿拉伯语字体
LV_FONT_DECLARE(font_arabic_14_1);
LV_FONT_DECLARE(font_arabic_16_4);

// Font Awesome 图标字体
LV_FONT_DECLARE(font_awesome_14_1);
LV_FONT_DECLARE(font_awesome_16_4);
LV_FONT_DECLARE(font_awesome_20_4);
LV_FONT_DECLARE(font_awesome_30_4);

#ifdef __cplusplus
}
#endif

#endif // MULTILANG_FONTS_H 
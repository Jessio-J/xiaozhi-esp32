#ifndef FONT_MULTILANG_14_1_H
#define FONT_MULTILANG_14_1_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

// Multi-language fonts with pre-configured fallback chain
// Chain: Chinese+Portuguese -> Thai -> Arabic
LV_FONT_DECLARE(font_multilang_chinese_portuguese_14_1);
LV_FONT_DECLARE(font_multilang_thai_14_1);
LV_FONT_DECLARE(font_multilang_arabic_14_1);

// Primary font (includes fallback chain)
#define FONT_MULTILANG_14_1 font_multilang_chinese_portuguese_14_1

#ifdef __cplusplus
}
#endif

#endif // FONT_MULTILANG_14_1_H

/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --force-fast-kern-format --no-compress --no-prefilter --font NotoSansThai-Regular.ttf --format lvgl --lv-include lvgl.h --bpp 1 -o src/font_multilang_thai_14_1.c --size 14 -r 0x20-0x7F --symbols •·÷×©¥®฀กขฃคฅฆงจฉชซฌญฎฏฐฑฒณดตถทธนบปผฝพฟภมยรฤลฦวศษสหฬอฮฯะัาำิีึืฺุู฻฼฽฾฿เแโใไๅๆ็่้๊๋์ํ๎๏๐๑๒๓๔๕๖๗๘๙๚๛๜๝๞๟๠๡๢๣๤๥๦๧๨๩๪๫๬๭๮๯๰๱๲๳๴๵๶๷๸๹๺๻๼๽๾๿
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
LV_FONT_DECLARE(font_multilang_chinese_portuguese);

#else
#include "lvgl.h"
#endif

#ifndef FONT_MULTILANG_THAI_14_1
#define FONT_MULTILANG_THAI_14_1 1
#endif

#if FONT_MULTILANG_THAI_14_1

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfe, 0xc0,

    /* U+0022 "\"" */
    0x99, 0x99,

    /* U+0023 "#" */
    0x12, 0x9, 0x4, 0x8f, 0xf1, 0x21, 0x23, 0xfc,
    0x48, 0x24, 0x12, 0x0,

    /* U+0024 "$" */
    0x11, 0xf9, 0x24, 0xf0, 0xe1, 0xc5, 0x17, 0xe1,
    0x4,

    /* U+0025 "%" */
    0x61, 0x24, 0x89, 0x22, 0x50, 0x95, 0x9a, 0x90,
    0xa4, 0x49, 0x12, 0x48, 0x60,

    /* U+0026 "&" */
    0x38, 0x11, 0x4, 0x41, 0xb0, 0x30, 0x16, 0x28,
    0xd2, 0x1c, 0xc7, 0x1f, 0x60,

    /* U+0027 "'" */
    0xf0,

    /* U+0028 "(" */
    0x69, 0x49, 0x24, 0x91, 0x26,

    /* U+0029 ")" */
    0xc9, 0x12, 0x49, 0x25, 0x2c,

    /* U+002A "*" */
    0x20, 0x8a, 0xde, 0x71, 0x60, 0x0,

    /* U+002B "+" */
    0x10, 0x20, 0x47, 0xf1, 0x2, 0x4, 0x0,

    /* U+002C "," */
    0xe8,

    /* U+002D "-" */
    0xe0,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0x8, 0xc4, 0x22, 0x11, 0x88, 0x46, 0x0,

    /* U+0030 "0" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x44,
    0x70,

    /* U+0031 "1" */
    0x37, 0x51, 0x11, 0x11, 0x11,

    /* U+0032 "2" */
    0x79, 0x8, 0x10, 0x20, 0xc1, 0x4, 0x10, 0x41,
    0xfc,

    /* U+0033 "3" */
    0x7a, 0x10, 0x43, 0x30, 0x30, 0x41, 0xf, 0xe0,

    /* U+0034 "4" */
    0x4, 0x18, 0x51, 0xa2, 0x48, 0xb1, 0x7f, 0x4,
    0x8,

    /* U+0035 "5" */
    0x7b, 0xc, 0x3e, 0xc, 0x10, 0x41, 0xb, 0xc0,

    /* U+0036 "6" */
    0x39, 0x8, 0x2e, 0xce, 0x18, 0x61, 0x4d, 0xe0,

    /* U+0037 "7" */
    0xfe, 0xc, 0x10, 0x60, 0x83, 0x4, 0x8, 0x20,
    0x40,

    /* U+0038 "8" */
    0x79, 0xa, 0x16, 0x67, 0x89, 0xa0, 0xc1, 0xc6,
    0xf8,

    /* U+0039 "9" */
    0x7b, 0x28, 0x61, 0x8d, 0xd0, 0x43, 0x9, 0xc0,

    /* U+003A ":" */
    0xc3,

    /* U+003B ";" */
    0x50, 0x1, 0x60,

    /* U+003C "<" */
    0x2, 0x18, 0xc6, 0xe, 0x3, 0x1, 0x80,

    /* U+003D "=" */
    0xfc, 0x0, 0x3f,

    /* U+003E ">" */
    0x80, 0xc0, 0xe0, 0x60, 0xce, 0x30, 0x0,

    /* U+003F "?" */
    0xf0, 0x42, 0x33, 0x21, 0x0, 0x42, 0x0,

    /* U+0040 "@" */
    0x1f, 0x6, 0x19, 0x3d, 0x6c, 0x99, 0x13, 0x22,
    0x64, 0x4c, 0x76, 0x40, 0xc, 0x0, 0x7c, 0x0,

    /* U+0041 "A" */
    0x8, 0xe, 0x5, 0x2, 0x82, 0x61, 0x11, 0xfc,
    0x82, 0x41, 0x40, 0xc0,

    /* U+0042 "B" */
    0xfd, 0xe, 0xc, 0x3f, 0x90, 0xe0, 0xc1, 0x87,
    0xf8,

    /* U+0043 "C" */
    0x3e, 0xc3, 0x4, 0x8, 0x10, 0x20, 0x60, 0x60,
    0x7c,

    /* U+0044 "D" */
    0xfc, 0x86, 0x83, 0x81, 0x81, 0x81, 0x81, 0x82,
    0x86, 0xf8,

    /* U+0045 "E" */
    0xfc, 0x21, 0xf, 0xc2, 0x10, 0x87, 0xc0,

    /* U+0046 "F" */
    0xfc, 0x21, 0xf, 0xc2, 0x10, 0x84, 0x0,

    /* U+0047 "G" */
    0x1f, 0x60, 0x40, 0x80, 0x87, 0x81, 0x81, 0xc1,
    0x61, 0x3f,

    /* U+0048 "H" */
    0x81, 0x81, 0x81, 0x81, 0xff, 0x81, 0x81, 0x81,
    0x81, 0x81,

    /* U+0049 "I" */
    0xe9, 0x24, 0x92, 0x5c,

    /* U+004A "J" */
    0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0xe0,

    /* U+004B "K" */
    0x85, 0x1a, 0x65, 0x8e, 0x1e, 0x24, 0x44, 0x8d,
    0xc,

    /* U+004C "L" */
    0x84, 0x21, 0x8, 0x42, 0x10, 0x87, 0xc0,

    /* U+004D "M" */
    0xc0, 0xf0, 0x3a, 0x16, 0x85, 0xb1, 0x64, 0x99,
    0x26, 0x39, 0x8c, 0x63, 0x10,

    /* U+004E "N" */
    0xc1, 0xc1, 0xa1, 0xb1, 0x91, 0x89, 0x8d, 0x85,
    0x83, 0x83,

    /* U+004F "O" */
    0x3e, 0x31, 0xb0, 0x70, 0x18, 0xc, 0x6, 0x3,
    0x83, 0x61, 0x1f, 0x0,

    /* U+0050 "P" */
    0xfa, 0x38, 0x61, 0x8f, 0xe8, 0x20, 0x82, 0x0,

    /* U+0051 "Q" */
    0x3e, 0x31, 0xb0, 0x70, 0x18, 0xc, 0x6, 0x3,
    0x83, 0x61, 0x1f, 0x1, 0x80, 0x60, 0x18,

    /* U+0052 "R" */
    0xf9, 0x1a, 0x14, 0x28, 0xdf, 0x26, 0x44, 0x85,
    0x8,

    /* U+0053 "S" */
    0x7e, 0x18, 0x20, 0x60, 0x60, 0x41, 0x7, 0xe0,

    /* U+0054 "T" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,
    0x20,

    /* U+0055 "U" */
    0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
    0x42, 0x3c,

    /* U+0056 "V" */
    0x81, 0x41, 0x43, 0x62, 0x26, 0x24, 0x34, 0x1c,
    0x18, 0x18,

    /* U+0057 "W" */
    0xc2, 0x1a, 0x28, 0x91, 0x44, 0x8a, 0x26, 0xd3,
    0x14, 0x50, 0xa2, 0x85, 0x14, 0x38, 0xe0, 0x82,
    0x0,

    /* U+0058 "X" */
    0x43, 0x62, 0x24, 0x1c, 0x18, 0x18, 0x34, 0x26,
    0x42, 0xc3,

    /* U+0059 "Y" */
    0x83, 0x8d, 0x11, 0x42, 0x82, 0x4, 0x8, 0x10,
    0x20,

    /* U+005A "Z" */
    0xfe, 0xc, 0x30, 0x41, 0x86, 0x8, 0x30, 0xc1,
    0xfc,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x92, 0x4e,

    /* U+005C "\\" */
    0xc2, 0x10, 0xc2, 0x10, 0x42, 0x18, 0x40,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x24, 0x9e,

    /* U+005E "^" */
    0x20, 0xc3, 0x12, 0x4a, 0x18, 0x40,

    /* U+005F "_" */
    0xfc,

    /* U+0060 "`" */
    0xb4,

    /* U+0061 "a" */
    0x78, 0x10, 0x5f, 0xc6, 0x18, 0xdd,

    /* U+0062 "b" */
    0x81, 0x2, 0x5, 0xcc, 0x50, 0x60, 0xc1, 0x83,
    0x8a, 0xe0,

    /* U+0063 "c" */
    0x3d, 0x8, 0x20, 0x82, 0x4, 0xf,

    /* U+0064 "d" */
    0x2, 0x4, 0x9, 0xd4, 0x70, 0x60, 0xc1, 0x82,
    0x8c, 0xe8,

    /* U+0065 "e" */
    0x79, 0x38, 0x7f, 0x82, 0x4, 0x4f,

    /* U+0066 "f" */
    0x3a, 0x11, 0xe4, 0x21, 0x8, 0x42, 0x10,

    /* U+0067 "g" */
    0x3a, 0x8e, 0xc, 0x18, 0x30, 0x51, 0xbd, 0x2,
    0x6, 0x1f, 0xe0,

    /* U+0068 "h" */
    0x82, 0x8, 0x2e, 0xc6, 0x18, 0x61, 0x86, 0x18,
    0x40,

    /* U+0069 "i" */
    0x9f, 0xe0,

    /* U+006A "j" */
    0x20, 0x12, 0x49, 0x24, 0x92, 0x70,

    /* U+006B "k" */
    0x82, 0x8, 0x22, 0x92, 0xce, 0x3c, 0x92, 0x68,
    0xc0,

    /* U+006C "l" */
    0xff, 0xe0,

    /* U+006D "m" */
    0xb9, 0xd8, 0xc6, 0x10, 0xc2, 0x18, 0x43, 0x8,
    0x61, 0xc, 0x21,

    /* U+006E "n" */
    0xbb, 0x18, 0x61, 0x86, 0x18, 0x61,

    /* U+006F "o" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x51, 0x1c,

    /* U+0070 "p" */
    0xb9, 0x8a, 0xc, 0x18, 0x30, 0x71, 0x5c, 0x81,
    0x2, 0x4, 0x0,

    /* U+0071 "q" */
    0x3a, 0x8e, 0xc, 0x18, 0x30, 0x51, 0x9d, 0x2,
    0x4, 0x8, 0x10,

    /* U+0072 "r" */
    0xbc, 0x88, 0x88, 0x88,

    /* U+0073 "s" */
    0x7c, 0x60, 0xc1, 0x84, 0x3e,

    /* U+0074 "t" */
    0x42, 0x3e, 0x84, 0x21, 0x8, 0x41, 0xc0,

    /* U+0075 "u" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0xdd,

    /* U+0076 "v" */
    0x82, 0x8d, 0x12, 0x22, 0xc5, 0xa, 0x8,

    /* U+0077 "w" */
    0xc4, 0x69, 0x49, 0x29, 0x25, 0x26, 0xac, 0x63,
    0xc, 0x61, 0x8c,

    /* U+0078 "x" */
    0x46, 0xc8, 0xa0, 0xc1, 0x85, 0x99, 0x23,

    /* U+0079 "y" */
    0x87, 0x89, 0x12, 0x26, 0x85, 0xa, 0x8, 0x10,
    0x60, 0x86, 0x0,

    /* U+007A "z" */
    0xf8, 0xc4, 0x42, 0x23, 0x1f,

    /* U+007B "{" */
    0x19, 0x8, 0x42, 0x13, 0x4, 0x21, 0x8, 0x41,
    0x80,

    /* U+007C "|" */
    0xff, 0xfe,

    /* U+007D "}" */
    0xc1, 0x8, 0x42, 0x10, 0x64, 0x21, 0x8, 0x4c,
    0x0,

    /* U+007E "~" */
    0xf3, 0x3c,

    /* U+00A5 "¥" */
    0x82, 0x89, 0x11, 0x42, 0x8f, 0x84, 0x3e, 0x10,
    0x20,

    /* U+00A9 "©" */
    0x1e, 0x18, 0x44, 0xea, 0x61, 0x90, 0x64, 0x19,
    0x6, 0x41, 0x4e, 0x98, 0x61, 0xe0,

    /* U+00AE "®" */
    0x1e, 0x18, 0x45, 0xca, 0x49, 0x92, 0x67, 0x19,
    0x46, 0x49, 0x52, 0x98, 0x61, 0xe0,

    /* U+00B7 "·" */
    0xc0,

    /* U+00D7 "×" */
    0x85, 0x23, 0xc, 0x4a, 0x10,

    /* U+00F7 "÷" */
    0x10, 0x20, 0x7, 0xf0, 0x2, 0x4, 0x0,

    /* U+0E01 "ก" */
    0x7a, 0x38, 0x59, 0x86, 0x18, 0x61,

    /* U+0E02 "ข" */
    0xca, 0x53, 0x18, 0xc6, 0x2e,

    /* U+0E03 "ฃ" */
    0x64, 0x96, 0x51, 0x45, 0x14, 0x4e,

    /* U+0E04 "ค" */
    0x7b, 0x38, 0x61, 0xf6, 0x18, 0x61,

    /* U+0E05 "ฅ" */
    0xfe, 0xd8, 0x61, 0xf6, 0x18, 0x61,

    /* U+0E06 "ฆ" */
    0x52, 0x65, 0x8a, 0x14, 0x28, 0x58, 0xae,

    /* U+0E07 "ง" */
    0x5c, 0x8d, 0x9, 0x12, 0x24, 0x4d, 0xc,

    /* U+0E08 "จ" */
    0x7a, 0x30, 0x59, 0x24, 0x92, 0xce,

    /* U+0E09 "ฉ" */
    0xf8, 0x30, 0x61, 0x86, 0x18, 0xdd,

    /* U+0E0A "ช" */
    0xca, 0x55, 0x18, 0xc6, 0x2e,

    /* U+0E0B "ซ" */
    0x64, 0x96, 0x91, 0x45, 0x14, 0x4e,

    /* U+0E0C "ฌ" */
    0x78, 0x31, 0x87, 0x10, 0xb2, 0x18, 0x43, 0x8,
    0x61, 0x8f, 0x2e,

    /* U+0E0D "ญ" */
    0x78, 0x63, 0x1c, 0x45, 0x91, 0x84, 0x61, 0x18,
    0x4f, 0x8d, 0x0, 0x41, 0x30, 0x78,

    /* U+0E0E "ฎ" */
    0x3c, 0x8d, 0x88, 0x92, 0x24, 0x48, 0xf1, 0x2,
    0x7c, 0x88,

    /* U+0E0F "ฏ" */
    0x3c, 0x8d, 0x9, 0x14, 0x28, 0x50, 0xe1, 0x2,
    0xfd, 0x78,

    /* U+0E10 "ฐ" */
    0x2, 0xfa, 0x20, 0x20, 0x4c, 0x89, 0x16, 0x38,
    0x1, 0xb6, 0xe0,

    /* U+0E11 "ฑ" */
    0xac, 0xe5, 0x8a, 0x14, 0x28, 0x50, 0xa1,

    /* U+0E12 "ฒ" */
    0x7c, 0x32, 0x86, 0x10, 0xc2, 0x18, 0x43, 0x8,
    0x71, 0x8b, 0xae,

    /* U+0E13 "ณ" */
    0x78, 0x61, 0x1c, 0x45, 0x91, 0x84, 0x61, 0x18,
    0x4f, 0x8d,

    /* U+0E14 "ด" */
    0x7d, 0x8e, 0xc, 0x18, 0x30, 0x70, 0xb9,

    /* U+0E15 "ต" */
    0x7f, 0x26, 0xc, 0x18, 0x30, 0x70, 0xb9,

    /* U+0E16 "ถ" */
    0x7a, 0x38, 0x59, 0x86, 0x18, 0x79,

    /* U+0E17 "ท" */
    0xbb, 0x18, 0x61, 0x86, 0x18, 0x61,

    /* U+0E18 "ธ" */
    0x7e, 0x85, 0x81, 0xe4, 0x68, 0x50, 0xbe,

    /* U+0E19 "น" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0xdd,

    /* U+0E1A "บ" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x5e,

    /* U+0E1B "ป" */
    0x4, 0x10, 0x61, 0x86, 0x18, 0x61, 0x86, 0x17,
    0x80,

    /* U+0E1C "ผ" */
    0xc3, 0x6, 0xc, 0x9a, 0xbd, 0xf1, 0xc1,

    /* U+0E1D "ฝ" */
    0x2, 0x4, 0xe, 0x18, 0x30, 0x64, 0xd5, 0xef,
    0x8e, 0x8,

    /* U+0E1E "พ" */
    0x99, 0x99, 0x9b, 0xab, 0xe6, 0x66, 0x66, 0x46,

    /* U+0E1F "ฟ" */
    0x1, 0x1, 0x1, 0x91, 0x9b, 0x9b, 0xaa, 0xae,
    0xe6, 0x66, 0x46,

    /* U+0E20 "ภ" */
    0x3c, 0x8d, 0x9, 0x14, 0x28, 0x50, 0xe1,

    /* U+0E21 "ม" */
    0x86, 0x18, 0x61, 0x86, 0x1c, 0x6e,

    /* U+0E22 "ย" */
    0x66, 0x18, 0x59, 0x86, 0x18, 0x5e,

    /* U+0E23 "ร" */
    0x7e, 0x8, 0x1c, 0x1c, 0x10, 0x7e,

    /* U+0E24 "ฤ" */
    0x7a, 0x38, 0x59, 0x86, 0x18, 0x79, 0x4, 0x10,
    0x40,

    /* U+0E25 "ล" */
    0x7a, 0x10, 0x5f, 0x86, 0x18, 0x5d,

    /* U+0E26 "ฦ" */
    0x3c, 0x8d, 0x9, 0x14, 0x28, 0x50, 0xe1, 0x2,
    0x4, 0x8,

    /* U+0E27 "ว" */
    0xf0, 0x82, 0x10, 0x84, 0x5e,

    /* U+0E28 "ศ" */
    0x7d, 0x9a, 0x14, 0x2f, 0x50, 0xa1, 0x42,

    /* U+0E29 "ษ" */
    0x85, 0xa, 0x15, 0x29, 0xf0, 0xa1, 0x3c,

    /* U+0E2A "ส" */
    0x2, 0xfa, 0x10, 0x27, 0xd0, 0xa1, 0x42, 0x74,

    /* U+0E2B "ห" */
    0x8a, 0x4b, 0xb3, 0x86, 0x18, 0x61,

    /* U+0E2C "ฬ" */
    0x1, 0xe, 0x82, 0x93, 0x9a, 0xaa, 0xaa, 0xa6,
    0x46, 0x46,

    /* U+0E2D "อ" */
    0xf8, 0x20, 0x79, 0x86, 0x1c, 0xde,

    /* U+0E2E "ฮ" */
    0x7, 0xf0, 0x81, 0xe6, 0x18, 0x73, 0x78,

    /* U+0E2F "ฯ" */
    0x66, 0x18, 0x61, 0x7c, 0x10, 0x41,

    /* U+0E30 "ะ" */
    0x8f, 0x0, 0x8f,

    /* U+0E31 "ั" */
    0x87, 0xc0,

    /* U+0E32 "า" */
    0xe1, 0x11, 0x11, 0x11,

    /* U+0E33 "ำ" */
    0xe0, 0xa0, 0xe0, 0x0, 0xe, 0x1, 0x1, 0x1,
    0x1, 0x1, 0x1, 0x1,

    /* U+0E34 "ิ" */
    0xfc,

    /* U+0E35 "ี" */
    0x7, 0xf0,

    /* U+0E36 "ึ" */
    0xc, 0x1b, 0xf0,

    /* U+0E37 "ื" */
    0x17, 0xf0,

    /* U+0E38 "ุ" */
    0xd4,

    /* U+0E39 "ู" */
    0x4a, 0x5e,

    /* U+0E3A "ฺ" */
    0xf0,

    /* U+0E3F "฿" */
    0x23, 0xea, 0x69, 0xa7, 0xea, 0x69, 0xa7, 0xe2,
    0x8,

    /* U+0E40 "เ" */
    0xaa, 0xab,

    /* U+0E41 "แ" */
    0x8a, 0x28, 0xa2, 0x8a, 0x28, 0xb3,

    /* U+0E42 "โ" */
    0xfa, 0x10, 0x84, 0x21, 0x8, 0x42, 0x10, 0xc0,

    /* U+0E43 "ใ" */
    0xe1, 0x12, 0x44, 0x44, 0x44, 0x47,

    /* U+0E44 "ไ" */
    0xf9, 0x8, 0x42, 0x10, 0x84, 0x21, 0x8, 0x60,

    /* U+0E45 "ๅ" */
    0xe1, 0x11, 0x11, 0x11, 0x11, 0x10,

    /* U+0E46 "ๆ" */
    0x6e, 0x58, 0x61, 0x64, 0x10, 0x41, 0x4, 0x10,
    0x40,

    /* U+0E47 "็" */
    0xfd, 0x76,

    /* U+0E48 "่" */
    0xe0,

    /* U+0E49 "้" */
    0xc4, 0xf0,

    /* U+0E4A "๊" */
    0xf2, 0x4d, 0xc0,

    /* U+0E4B "๋" */
    0x5d, 0x0,

    /* U+0E4C "์" */
    0xf0,

    /* U+0E4D "ํ" */
    0xf7, 0x80,

    /* U+0E4E "๎" */
    0x3a, 0x0,

    /* U+0E4F "๏" */
    0x7d, 0x8e, 0xed, 0xdb, 0xb8, 0xdf, 0x0,

    /* U+0E50 "๐" */
    0x7b, 0x38, 0x61, 0x87, 0x37, 0x80,

    /* U+0E51 "๑" */
    0x7a, 0x38, 0x61, 0x64, 0x33, 0x80,

    /* U+0E52 "๒" */
    0x81, 0x2, 0xdd, 0x5a, 0x36, 0x60, 0xe3, 0x7c,

    /* U+0E53 "๓" */
    0x7e, 0x58, 0x61, 0x86, 0x16, 0x40,

    /* U+0E54 "๔" */
    0x4, 0x17, 0xb0, 0x82, 0x79, 0x24, 0x7c,

    /* U+0E55 "๕" */
    0x65, 0x57, 0xb0, 0x82, 0x79, 0x24, 0x7c,

    /* U+0E56 "๖" */
    0x83, 0x7, 0x93, 0x4, 0x10, 0x53, 0x78,

    /* U+0E57 "๗" */
    0x1, 0x1, 0x7d, 0x95, 0x85, 0x85, 0x85, 0x85,
    0x66,

    /* U+0E58 "๘" */
    0x4, 0x17, 0xb0, 0x82, 0x18, 0x7d, 0x78,

    /* U+0E59 "๙" */
    0x4, 0x17, 0xec, 0x92, 0x48, 0xa2, 0x64,

    /* U+0E5A "๚" */
    0x64, 0xc2, 0x61, 0x30, 0x97, 0xf8, 0x24, 0x12,
    0x9,

    /* U+0E5B "๛" */
    0x70, 0x26, 0xa9, 0xfa, 0x3d, 0x70, 0x0,

    /* U+2022 "•" */
    0xff, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 58, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 60, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 91, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 5, .adv_w = 145, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 26, .adv_w = 186, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 39, .adv_w = 164, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 50, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 53, .adv_w = 67, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 58, .adv_w = 67, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 63, .adv_w = 123, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 69, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 76, .adv_w = 60, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 77, .adv_w = 72, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 78, .adv_w = 60, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 79, .adv_w = 83, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 86, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 95, .adv_w = 128, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 151, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 60, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 60, .box_w = 2, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 172, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 179, .adv_w = 128, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 182, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 189, .adv_w = 97, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 201, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 212, .adv_w = 143, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 224, .adv_w = 146, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 242, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 252, .adv_w = 125, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 116, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 266, .adv_w = 163, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 276, .adv_w = 166, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 76, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 290, .adv_w = 61, .box_w = 4, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 297, .adv_w = 139, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 117, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 313, .adv_w = 203, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 170, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 336, .adv_w = 175, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 348, .adv_w = 136, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 356, .adv_w = 175, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 371, .adv_w = 139, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 380, .adv_w = 123, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 125, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 397, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 407, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 417, .adv_w = 208, .box_w = 13, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 434, .adv_w = 131, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 127, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 453, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 462, .adv_w = 74, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 467, .adv_w = 83, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 474, .adv_w = 74, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 479, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 485, .adv_w = 99, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 486, .adv_w = 63, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 487, .adv_w = 126, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 493, .adv_w = 138, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 503, .adv_w = 108, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 509, .adv_w = 138, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 519, .adv_w = 126, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 525, .adv_w = 77, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 532, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 543, .adv_w = 138, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 552, .adv_w = 58, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 554, .adv_w = 58, .box_w = 3, .box_h = 15, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 560, .adv_w = 120, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 569, .adv_w = 58, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 571, .adv_w = 209, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 138, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 588, .adv_w = 136, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 595, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 606, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 617, .adv_w = 93, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 621, .adv_w = 107, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 626, .adv_w = 81, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 633, .adv_w = 138, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 639, .adv_w = 114, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 646, .adv_w = 176, .box_w = 11, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 657, .adv_w = 118, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 664, .adv_w = 114, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 675, .adv_w = 105, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 680, .adv_w = 85, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 689, .adv_w = 123, .box_w = 1, .box_h = 15, .ofs_x = 3, .ofs_y = -4},
    {.bitmap_index = 691, .adv_w = 85, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 700, .adv_w = 128, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 702, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 711, .adv_w = 186, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 725, .adv_w = 186, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 739, .adv_w = 60, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 740, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 745, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 752, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 758, .adv_w = 123, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 763, .adv_w = 123, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 769, .adv_w = 138, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 775, .adv_w = 139, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 781, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 788, .adv_w = 120, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 795, .adv_w = 119, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 801, .adv_w = 135, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 807, .adv_w = 123, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 812, .adv_w = 125, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 818, .adv_w = 203, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 829, .adv_w = 204, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 843, .adv_w = 135, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 853, .adv_w = 135, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 863, .adv_w = 123, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 874, .adv_w = 140, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 881, .adv_w = 202, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 892, .adv_w = 204, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 902, .adv_w = 138, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 909, .adv_w = 142, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 916, .adv_w = 135, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 922, .adv_w = 136, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 928, .adv_w = 122, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 935, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 941, .adv_w = 135, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 947, .adv_w = 136, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 956, .adv_w = 145, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 963, .adv_w = 146, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 973, .adv_w = 156, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 981, .adv_w = 153, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 992, .adv_w = 135, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 999, .adv_w = 138, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1005, .adv_w = 133, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1011, .adv_w = 109, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1017, .adv_w = 135, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1026, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1032, .adv_w = 135, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1042, .adv_w = 110, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1047, .adv_w = 141, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1054, .adv_w = 143, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1061, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1069, .adv_w = 131, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1075, .adv_w = 150, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1085, .adv_w = 129, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1091, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1098, .adv_w = 116, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1104, .adv_w = 76, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1107, .adv_w = 0, .box_w = 5, .box_h = 2, .ofs_x = -5, .ofs_y = 9},
    {.bitmap_index = 1109, .adv_w = 91, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1113, .adv_w = 91, .box_w = 8, .box_h = 12, .ofs_x = -4, .ofs_y = 0},
    {.bitmap_index = 1125, .adv_w = 0, .box_w = 6, .box_h = 1, .ofs_x = -7, .ofs_y = 9},
    {.bitmap_index = 1126, .adv_w = 0, .box_w = 6, .box_h = 2, .ofs_x = -7, .ofs_y = 9},
    {.bitmap_index = 1128, .adv_w = 0, .box_w = 7, .box_h = 3, .ofs_x = -8, .ofs_y = 9},
    {.bitmap_index = 1131, .adv_w = 0, .box_w = 6, .box_h = 2, .ofs_x = -7, .ofs_y = 9},
    {.bitmap_index = 1133, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = -3, .ofs_y = -4},
    {.bitmap_index = 1134, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = -6, .ofs_y = -4},
    {.bitmap_index = 1136, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = -3, .ofs_y = -3},
    {.bitmap_index = 1137, .adv_w = 131, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1146, .adv_w = 66, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1148, .adv_w = 127, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1154, .adv_w = 69, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1162, .adv_w = 65, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1168, .adv_w = 68, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1176, .adv_w = 91, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1182, .adv_w = 133, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1191, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = -6, .ofs_y = 9},
    {.bitmap_index = 1193, .adv_w = 0, .box_w = 1, .box_h = 3, .ofs_x = -2, .ofs_y = 9},
    {.bitmap_index = 1194, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = -5, .ofs_y = 9},
    {.bitmap_index = 1196, .adv_w = 0, .box_w = 6, .box_h = 3, .ofs_x = -6, .ofs_y = 9},
    {.bitmap_index = 1199, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = -4, .ofs_y = 9},
    {.bitmap_index = 1201, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = -4, .ofs_y = 9},
    {.bitmap_index = 1202, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = -4, .ofs_y = 9},
    {.bitmap_index = 1204, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = -4, .ofs_y = 9},
    {.bitmap_index = 1206, .adv_w = 133, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1213, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1219, .adv_w = 122, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1225, .adv_w = 137, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1233, .adv_w = 125, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1239, .adv_w = 121, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1246, .adv_w = 121, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1253, .adv_w = 116, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1260, .adv_w = 161, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1269, .adv_w = 127, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1276, .adv_w = 113, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1283, .adv_w = 172, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1292, .adv_w = 195, .box_w = 10, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1299, .adv_w = 84, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 4}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x4, 0x9, 0x12, 0x32, 0x52
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 165, .range_length = 83, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 6, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 3585, .range_length = 58, .glyph_id_start = 102,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 3647, .range_length = 29, .glyph_id_start = 160,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 8226, .range_length = 1, .glyph_id_start = 189,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 5,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t font_multilang_thai_14_1 = {
#else
lv_font_t font_multilang_thai_14_1 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if FONT_MULTILANG_THAI_14_1*/


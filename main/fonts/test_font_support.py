#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
字体支持检测脚本
用于检测字体文件是否支持特定语言的字符
"""

import os
from fontTools.ttLib import TTFont

def test_font_support(font_path, chars, lang_name):
    """测试字体是否支持指定字符"""
    if not os.path.exists(font_path):
        print(f"❌ 字体文件 {font_path} 不存在")
        return False
    
    try:
        font = TTFont(font_path)
        cmap = font.getBestCmap()
        
        supported = []
        unsupported = []
        
        for char in chars:
            unicode_val = ord(char)
            if unicode_val in cmap:
                supported.append(char)
            else:
                unsupported.append(char)
        
        support_rate = len(supported) / len(chars) * 100
        
        print(f"\n=== {lang_name} 字符支持情况 ===")
        print(f"字体文件: {font_path}")
        print(f"总字符数: {len(chars)}")
        print(f"支持字符数: {len(supported)}")
        print(f"不支持字符数: {len(unsupported)}")
        print(f"支持率: {support_rate:.1f}%")
        
        if unsupported:
            print(f"不支持的字符: {''.join(unsupported[:20])}")  # 只显示前20个
            if len(unsupported) > 20:
                print(f"... 还有 {len(unsupported) - 20} 个字符")
        
        return support_rate >= 90  # 90%以上认为支持良好
        
    except Exception as e:
        print(f"❌ 测试字体时出错: {e}")
        return False

def get_test_chars():
    """获取测试字符集"""
    test_sets = {
        '葡萄牙语': [
            'á', 'à', 'â', 'ã', 'é', 'ê', 'í', 'ó', 'ô', 'õ', 'ú', 'ç',
            'Á', 'À', 'Â', 'Ã', 'É', 'Ê', 'Í', 'Ó', 'Ô', 'Õ', 'Ú', 'Ç'
        ],
        '泰语': [
            # 泰语常用字符 (排除保留码点和特殊符号)
            # 泰语辅音 (U+0E01-0E2E)
            *[chr(i) for i in range(0x0E01, 0x0E2F)],
            # 泰语元音 (U+0E30-0E3A) 
            *[chr(i) for i in range(0x0E30, 0x0E3B)],
            # 泰语符号 (U+0E3F-0E5B，排除一些特殊符号)
            *[chr(i) for i in range(0x0E3F, 0x0E5C)],
            # 泰语数字 (U+0E50-0E59)
            *[chr(i) for i in range(0x0E50, 0x0E5A)],
        ],
        '阿拉伯语': [
            # 阿拉伯语常用字符 (排除扩展和特殊符号)
            *[chr(i) for i in range(0x0627, 0x064B)],  # 基本阿拉伯字母
            *[chr(i) for i in range(0x0660, 0x066A)],  # 阿拉伯数字
        ]
    }
    return test_sets

def main():
    print("字体多语言支持检测工具")
    print("=" * 50)
    
    # 要测试的字体文件
    fonts_to_test = [
        "AlibabaPuHuiTi-3-55-Regular.ttf",
        "NotoSansThai-Regular.ttf",
        "NotoSansArabic-Regular.ttf"
    ]
    
    test_chars = get_test_chars()
    
    for font_path in fonts_to_test:
        print(f"\n🔍 测试字体: {font_path}")
        
        if not os.path.exists(font_path):
            print(f"❌ 字体文件不存在，跳过测试")
            continue
        
        # 测试每种语言
        for lang_name, chars in test_chars.items():
            support = test_font_support(font_path, chars, lang_name)
            
            if support:
                print(f"✅ {font_path} 良好支持 {lang_name}")
            else:
                print(f"⚠️  {font_path} 对 {lang_name} 支持不足")
    
    # 给出建议
    print(f"\n📋 建议:")
    print(f"1. 葡萄牙语: 使用 AlibabaPuHuiTi-3-55-Regular.ttf")
    print(f"2. 泰语: 下载 NotoSansThai-Regular.ttf")
    print(f"   下载地址: https://fonts.google.com/noto/specimen/Noto+Sans+Thai")
    print(f"3. 阿拉伯语: 下载 NotoSansArabic-Regular.ttf")
    print(f"   下载地址: https://fonts.google.com/noto/specimen/Noto+Sans+Arabic")

if __name__ == "__main__":

    main()
 
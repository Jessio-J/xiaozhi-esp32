#!/usr/bin/env python3
"""
字体链生成器 - 生成已配置好fallback链的LVGL字体
"""

import os
import sys
import argparse
import re

def parse_arguments():
    parser = argparse.ArgumentParser(description='Generate LVGL fonts with pre-configured fallback chains')
    parser.add_argument('--font-size', type=int, default=14, help='Font size (default: 14)')
    parser.add_argument('--bpp', type=int, default=1, help='Bits per pixel (default: 1)')
    parser.add_argument('--output-name', default='font_multilang', help='Output font name prefix')
    return parser.parse_args()

def generate_single_font(font_file, symbols, output_name, font_size, bpp):
    """生成单个字体文件"""
    flags = "--force-fast-kern-format --no-compress --no-prefilter"
    ascii_range = "-r 0x20-0x7F"
    symbols_str = "".join(symbols)
    
    output = f"src/{output_name}_{font_size}_{bpp}.c"
    cmd = f"lv_font_conv {flags} --font {font_file} --format lvgl --lv-include lvgl.h --bpp {bpp} -o {output} --size {font_size} {ascii_range} --symbols {symbols_str}"
    
    print(f"Generating {output}")
    ret = os.system(cmd)
    return ret == 0, output

def get_font_symbols():
    """获取各语言字符集"""
    # 基本符号
    basic_symbols = ["•", "·", "÷", "×", "©", "¥", "®"]
    
    # 中文字符
    chinese_symbols = []
    if os.path.exists("GB2312.TXT"):
        for line in open("GB2312.TXT"):
            if line.startswith("#") or line.strip() == "":
                continue
            parts = line.split()
            unicode = int(parts[1], 16)
            chinese_symbols.append(chr(unicode))
    
    # 葡萄牙语字符
    portuguese_symbols = [
        'á', 'à', 'â', 'ã', 'é', 'ê', 'í', 'ó', 'ô', 'õ', 'ú', 'ç',
        'Á', 'À', 'Â', 'Ã', 'É', 'Ê', 'Í', 'Ó', 'Ô', 'Õ', 'Ú', 'Ç'
    ]
    
    # 泰语字符
    thai_symbols = [chr(i) for i in range(0x0E00, 0x0E80)]
    
    # 阿拉伯语字符
    arabic_symbols = []
    arabic_symbols.extend([chr(i) for i in range(0x0600, 0x0700)])  # 基本阿拉伯语
    arabic_symbols.extend([chr(i) for i in range(0x0750, 0x0780)])  # 阿拉伯语扩展
    
    return {
        'chinese_portuguese': basic_symbols + chinese_symbols + portuguese_symbols,
        'thai': basic_symbols + thai_symbols,
        'arabic': basic_symbols + arabic_symbols
    }

def modify_font_file(file_path, font_name, fallback_font=None):
    """修改生成的字体文件，添加fallback指针"""
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 找到字体定义的位置
    pattern = rf'(const lv_font_t {font_name} = \{{[^}}]+\#if LV_VERSION_CHECK\(8, 2, 0\) \|\| LVGL_VERSION_MAJOR >= 9\s+\.fallback = )NULL(,\s+\#endif)'
    
    fallback_value = f'&{fallback_font}' if fallback_font else 'NULL'
    replacement = f'\\g<1>{fallback_value}\\g<2>'
    
    modified_content = re.sub(pattern, replacement, content, flags=re.DOTALL)
    
    # 如果没有找到模式，尝试另一种模式 (旧版本LVGL)
    if modified_content == content:
        # 对于没有fallback字段的旧版本，我们需要添加声明
        if fallback_font:
            # 在文件开头添加fallback字体的声明
            declaration = f'LV_FONT_DECLARE({fallback_font});\n\n'
            if declaration not in modified_content:
                # 找到第一个包含语句后插入
                include_pattern = r'(#include[^\n]+\n)'
                modified_content = re.sub(include_pattern, f'\\1{declaration}', modified_content, count=1)
    
    with open(file_path, 'w', encoding='utf-8') as f:
        f.write(modified_content)
    
    return modified_content != content

def generate_fallback_fonts(font_size, bpp, output_name):
    """生成带fallback链的字体"""
    symbols = get_font_symbols()
    
    # 字体文件映射
    font_files = {
        'chinese_portuguese': 'AlibabaPuHuiTi-3-55-Regular.ttf',
        'thai': 'NotoSansThai-Regular.ttf',
        'arabic': 'NotoSansArabic-Regular.ttf'
    }
    
    # 生成的字体名称
    font_names = {
        'chinese_portuguese': f'{output_name}_chinese_portuguese',
        'thai': f'{output_name}_thai', 
        'arabic': f'{output_name}_arabic'
    }
    
    generated_files = {}
    
    # 先生成各个独立字体
    for lang, symbols_list in symbols.items():
        font_file = font_files[lang]
        if not os.path.exists(font_file):
            print(f"Warning: Font file {font_file} not found, skipping {lang}")
            continue
            
        success, output_file = generate_single_font(
            font_file, symbols_list, font_names[lang], font_size, bpp
        )
        
        if success:
            generated_files[lang] = (output_file, font_names[lang])
            print(f"✓ Generated {lang} font: {output_file}")
        else:
            print(f"✗ Failed to generate {lang} font")
    
    # 设置fallback链：chinese_portuguese -> thai -> arabic
    fallback_chain = ['arabic', 'thai', 'chinese_portuguese']  # 反向，因为我们从后往前设置
    
    for i in range(len(fallback_chain) - 1):
        current_lang = fallback_chain[i]
        next_lang = fallback_chain[i + 1]
        
        if current_lang in generated_files and next_lang in generated_files:
            current_file, current_name = generated_files[current_lang]
            _, next_name = generated_files[next_lang]
            
            print(f"Setting fallback: {current_name} -> {next_name}")
            if modify_font_file(current_file, current_name, next_name):
                print(f"✓ Successfully set fallback for {current_name}")
            else:
                print(f"✗ Failed to set fallback for {current_name}")
    
    # 生成头文件声明
    generate_header_file(font_names, font_size, bpp, output_name)
    
    return generated_files

def generate_header_file(font_names, font_size, bpp, output_name):
    """生成头文件"""
    header_content = f'''#ifndef {output_name.upper()}_{font_size}_{bpp}_H
#define {output_name.upper()}_{font_size}_{bpp}_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {{
#endif

// Multi-language fonts with pre-configured fallback chain
// Chain: Chinese+Portuguese -> Thai -> Arabic
'''
    
    for lang, font_name in font_names.items():
        header_content += f'LV_FONT_DECLARE({font_name}_{font_size}_{bpp});\n'
    
    header_content += f'''
// Primary font (includes fallback chain)
#define {output_name.upper()}_{font_size}_{bpp} {font_names.get('chinese_portuguese', 'font_primary')}_{font_size}_{bpp}

#ifdef __cplusplus
}}
#endif

#endif // {output_name.upper()}_{font_size}_{bpp}_H
'''
    
    header_file = f"{output_name}_{font_size}_{bpp}.h"
    with open(header_file, 'w') as f:
        f.write(header_content)
    
    print(f"✓ Generated header file: {header_file}")

def main():
    args = parse_arguments()
    
    print(f"Generating multi-language fonts with fallback chain...")
    print(f"Font size: {args.font_size}px, BPP: {args.bpp}")
    print(f"Fallback chain: Chinese+Portuguese -> Thai -> Arabic")
    
    generated_files = generate_fallback_fonts(args.font_size, args.bpp, args.output_name)
    
    if generated_files:
        print(f"\n✓ Successfully generated {len(generated_files)} fonts with fallback chain")
        print("Usage in your code:")
        print(f'#include "{args.output_name}_{args.font_size}_{args.bpp}.h"')
        print(f'// Use {args.output_name.upper()}_{args.font_size}_{args.bpp} as your primary font')
    else:
        print("\n✗ No fonts were generated successfully")

if __name__ == "__main__":
    main() 
import os
import sys
import argparse

def parse_arguments():
    parser = argparse.ArgumentParser(description='Multi-language font converter utility')
    parser.add_argument('type', choices=['lvgl', 'dump'], help='Output type: lvgl or dump')
    parser.add_argument('--font-size', type=int, default=14, help='Font size (default: 14)')
    parser.add_argument('--bpp', type=int, default=4, help='Bits per pixel (default: 4)')
    parser.add_argument('--lang', choices=['portuguese', 'thai', 'arabic', 'all'], default='all', help='Language to generate')
    return parser.parse_args()

def get_portuguese_chars():
    """葡萄牙语字符 - 可以用普惠体"""
    return [
        'á', 'à', 'â', 'ã', 'é', 'ê', 'í', 'ó', 'ô', 'õ', 'ú', 'ç',
        'Á', 'À', 'Â', 'Ã', 'É', 'Ê', 'Í', 'Ó', 'Ô', 'Õ', 'Ú', 'Ç'
    ]

def get_thai_chars():
    """泰语字符 - 需要专门的泰语字体"""
    return [chr(i) for i in range(0x0E00, 0x0E80)]

def get_arabic_chars():
    """阿拉伯语字符 - 需要专门的阿拉伯语字体"""
    chars = []
    chars.extend([chr(i) for i in range(0x0600, 0x0700)])  # 基本阿拉伯语
    chars.extend([chr(i) for i in range(0x0750, 0x0780)])  # 阿拉伯语扩展
    return chars

def load_chinese_symbols():
    """加载中文字符"""
    symbols = []
    for line in open("GB2312.TXT"):
        if line.startswith("#") or line.strip() == "":
            continue
        parts = line.split()
        unicode = int(parts[1], 16)
        symbols.append(chr(unicode))
    return symbols

def generate_font(font_file, output_name, symbols, font_size, bpp):
    """生成字体文件"""
    flags = "--force-fast-kern-format --no-compress --no-prefilter"
    
    # 基本ASCII字符范围
    ascii_range = "-r 0x20-0x7F"
    
    # 创建符号字符串
    symbols_str = "".join(symbols)
    
    output = f"src/{output_name}_{font_size}_{bpp}.c"
    cmd = f"lv_font_conv {flags} --font {font_file} --format lvgl --lv-include lvgl.h --bpp {bpp} -o {output} --size {font_size} {ascii_range} --symbols {symbols_str}"
    
    print(f"Generating {output}")
    print(f"Total symbols: {len(symbols_str)}")
    
    ret = os.system(cmd)
    if ret != 0:
        print(f"字体生成失败，返回码：{ret}")
        return False
    else:
        print("字体生成成功")
        return True

def main():
    args = parse_arguments()
    
    # 基本符号
    basic_symbols = ["•", "·", "÷", "×", "©", "¥", "®"]
    
    if args.lang == 'portuguese' or args.lang == 'all':
        # 生成葡萄牙语字体 (使用普惠体)
        print("\n=== 生成葡萄牙语字体 ===")
        portuguese_symbols = basic_symbols + get_portuguese_chars() + load_chinese_symbols()
        generate_font(
            "AlibabaPuHuiTi-3-55-Regular.ttf",
            "font_portuguese",
            portuguese_symbols,
            args.font_size,
            args.bpp
        )
    
    if args.lang == 'thai' or args.lang == 'all':
        # 生成泰语字体 (需要泰语字体文件)
        print("\n=== 生成泰语字体 ===")
        thai_font = "NotoSansThai-Regular.ttf"  # 需要下载
        if os.path.exists(thai_font):
            thai_symbols = basic_symbols + get_thai_chars()
            generate_font(thai_font, "font_thai", thai_symbols, args.font_size, args.bpp)
        else:
            print(f"泰语字体文件 {thai_font} 不存在，请下载后重试")
            print("下载地址: https://fonts.google.com/noto/specimen/Noto+Sans+Thai")
    
    if args.lang == 'arabic' or args.lang == 'all':
        # 生成阿拉伯语字体 (需要阿拉伯语字体文件)
        print("\n=== 生成阿拉伯语字体 ===")
        arabic_font = "NotoSansArabic-Regular.ttf"  # 需要下载
        if os.path.exists(arabic_font):
            arabic_symbols = basic_symbols + get_arabic_chars()
            generate_font(arabic_font, "font_arabic", arabic_symbols, args.font_size, args.bpp)
        else:
            print(f"阿拉伯语字体文件 {arabic_font} 不存在，请下载后重试")
            print("下载地址: https://fonts.google.com/noto/specimen/Noto+Sans+Arabic")

if __name__ == "__main__":
    main() 
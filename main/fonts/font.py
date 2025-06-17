import os
import sys
import argparse

def parse_arguments():
    parser = argparse.ArgumentParser(description='Font converter utility')
    parser.add_argument('type', choices=['lvgl', 'dump'], help='Output type: lvgl or dump')
    parser.add_argument('--font-size', type=int, default=14, help='Font size (default: 14)')
    parser.add_argument('--bpp', type=int, default=4, help='Bits per pixel (default: 4)')
    return parser.parse_args()

def load_symbols():
    symbols = ["•", "·", "÷", "×", "©", "¥", "®"]
    
    # 添加葡萄牙语字符
    portuguese_chars = [
        'á', 'à', 'â', 'ã', 'é', 'ê', 'í', 'ó', 'ô', 'õ', 'ú', 'ç',
        'Á', 'À', 'Â', 'Ã', 'É', 'Ê', 'Í', 'Ó', 'Ô', 'Õ', 'Ú', 'Ç'
    ]
    symbols.extend(portuguese_chars)
    
    # 添加泰语字符 (U+0E00-U+0E7F)
    for i in range(0x0E00, 0x0E80):
        symbols.append(chr(i))
    
    # 添加阿拉伯语字符 (U+0600-U+06FF, U+0750-U+077F)
    for i in range(0x0600, 0x0700):  # 基本阿拉伯语
        symbols.append(chr(i))
    for i in range(0x0750, 0x0780):  # 阿拉伯语扩展
        symbols.append(chr(i))
    
    # 原有的中文字符
    for line in open("GB2312.TXT"):
        if line.startswith("#") or line.strip() == "":
            continue
        parts = line.split()
        unicode = int(parts[1], 16)
        symbols.append(chr(unicode))
    return symbols

def main():
    args = parse_arguments()
    
    font = "AlibabaPuHuiTi-3-55-Regular.ttf"
    flags = "--force-fast-kern-format --no-compress --no-prefilter"
    
    symbols = load_symbols()
    
    if args.type == "lvgl":
        output = f"src/font_puhui_{args.font_size}_{args.bpp}.c"
        symbols_str = "".join(symbols)
        cmd = f"lv_font_conv {flags} --font {font} --format lvgl --lv-include lvgl.h --bpp {args.bpp} -o {output} --size {args.font_size} -r 0x20-0x7F --symbols {symbols_str}"
    else:  # dump
        output = f"./dump"
        symbols_str = "欢迎使用小智聊天机器人，这是一个纯手工打造的人工智能硬件产品。"
        cmd = f"lv_font_conv {flags} --font {font} --format dump --bpp {args.bpp} -o {output} --size {args.font_size} -r 0x20-0x7F --symbols {symbols_str}"

    print("Total symbols:", len(symbols_str))
    print("Generating", output)

    ret = os.system(cmd)
    if ret != 0:
        print(f"命令执行失败，返回码：{ret}")
    else:
        print("命令执行成功")

if __name__ == "__main__":
    main()


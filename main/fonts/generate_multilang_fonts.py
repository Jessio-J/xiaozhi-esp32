import os

# 定义多语言字体配置
multilang_configs = [
    # (语言, 字体大小, bpp)
    ('portuguese', 14, 1),  # 葡萄牙语，适合OLED
    ('portuguese', 16, 4),  # 葡萄牙语，适合彩色LCD
    ('portuguese', 20, 4),
    ('thai', 14, 1),        # 泰语
    ('thai', 16, 4),
    ('arabic', 14, 1),      # 阿拉伯语
    ('arabic', 16, 4),
]

def main():
    print("开始生成多语言字体...")
    
    # 首先生成更新的中文+葡萄牙语字体（使用修改后的font.py）
    print("\n=== 生成包含葡萄牙语的中文字体 ===")
    for size, bpp in [(14, 1), (16, 4), (20, 4), (30, 4)]:
        print(f"正在生成 {size}px 字体，{bpp} bpp（包含葡萄牙语）...")
        cmd = f"python font.py lvgl --font-size {size} --bpp {bpp}"
        ret = os.system(cmd)
        if ret != 0:
            print(f"生成失败")
        else:
            print(f"生成成功")
    
    # 然后生成独立的多语言字体
    print("\n=== 生成独立多语言字体 ===")
    for lang, size, bpp in multilang_configs:
        print(f"\n正在生成 {lang} {size}px 字体，{bpp} bpp...")
        
        cmd = f"python multilang_font.py lvgl --font-size {size} --bpp {bpp} --lang {lang}"
        ret = os.system(cmd)
        
        if ret != 0:
            print(f"生成 {lang} {size}px 字体失败")
        else:
            print(f"生成 {lang} {size}px 字体成功")

if __name__ == "__main__":
    main() 
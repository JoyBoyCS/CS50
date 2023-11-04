import sys
from pyfiglet import Figlet
import random

# 创建一个字体列表
available_fonts = ['slant', '3d', 'univers', 'rectangles', 'alphabet']  # 在这插入你的字体库

if len(sys.argv) == 1:
    # 如果没有额外参数,使用随机字体
    chosen_font = random.choice(available_fonts)
    figlet = Figlet(font=chosen_font)
elif len(sys.argv) == 3 and sys.argv[1] in ['-f', '--font'] and sys.argv[2] in available_fonts:
    # 如果有两个有效参数, 使用指定字体
    figlet = Figlet(font=sys.argv[2])
else:
    sys.exit("Invalid usage")

s = input('Input:')
print(f'Output:\n{figlet.renderText(s)}')
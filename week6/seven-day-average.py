import csv
import requests
from collections import defaultdict

def main():
    # 读取 NYTimes 的 Covid 数据库
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")  # 解码内容
    file = decoded_content.splitlines()  # 按行切割
    reader = csv.DictReader(file)  # 使用csv模块中的DictReader类来读取数据

    # 构建每个州14天内新病例的列表
    new_cases = calculate(reader)

    # 创建一个列表来保存选定的州
    states = []
    print("选择一个或多个州查看平均COVID病例数.")
    print("完成后按回车.\n")

    while True:
        state = input("州名: ")
        if state in new_cases:  # 如果输入的州在 new_cases 中,添加到 states 列表里
            states.append(state)
        if len(state) == 0:  # 如果用户没有输入任何内容(只按了回车),则退出循环
            break

    print(f"\n七天平均值")

    # 打印本周与上周的七天平均值
    comparative_averages(new_cases, states)


# 计算每个州的最近14天的新病例数量
def calculate(reader):
    new_cases = defaultdict(list)
    prev_case = defaultdict(int)
    for row in reader:
        state = row['state']
        cases = int(row['cases'])
        if prev_case[state]:
            new_cases[state].append(cases - prev_case[state])
            if len(new_cases[state]) > 14:  # 如果超过14天,则去掉最早的数据
                new_cases[state].pop(0)
        prev_case[state] = cases
    return new_cases


# 计算并打印给定州的七天平均值
def comparative_averages(new_cases, states):
    for state in states:
        if len(new_cases[state]) >= 14:
            average_this_week = sum(new_cases[state][-7:]) / 7
            average_last_week = sum(new_cases[state][-14:-7]) / 7
            print(f"{state}: 本周平均每日新病例数 {average_this_week:.2f}, 上周 {average_last_week:.2f}")
        else:
            print(f"{state} 的数据不足,无法计算")


main()
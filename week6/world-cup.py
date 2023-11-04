# 模拟一场体育比赛

import csv
import sys
import random

# 运行模拟的次数
N = 1000


def main():

    # 确保正确使用
    if len(sys.argv) != 2 or len(sys.argv) == 2 and sys.argv[1] not in ['2018m.csv', '2019w.csv']:
        sys.exit("用法: python tournament.py 文件名")

    teams = []

    with open(sys.argv[1], 'r') as f:
        reader = csv.DictReader(f)

        for row in reader:
            team = {
                'team': row['team'],
                'rating': int(row['rating'])
            }
            teams.append(team)

    counts = {team['team']: 0 for team in teams}  # 初始化每个队伍的获胜次数为0

    # 模拟 N 场比赛并记录胜场数
    for i in range(N):
        winner = simulate_tournament(teams)
        counts[winner] += 1

    # 根据模拟结果打印每个队伍的获胜概率
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% 获胜概率")


def simulate_game(team1, team2):
    """模拟一场比赛.如果 team1 胜利则返回 True,否则返回 False."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """模拟一轮比赛.返回赢家队伍列表."""
    winners = []

    # 对所有队伍配对模拟比赛
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """模拟一场比赛.返回获胜队伍的名字."""
    while len(teams) > 1:
        teams = simulate_round(teams)

    return teams[0]['team']  # 返回获胜队伍的名称

if __name__ == "__main__":
    main()
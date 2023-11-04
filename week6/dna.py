import csv
import sys

def main():
    # TODO: 检查命令行使用方式
    if len(sys.argv) != 3:
        sys.exit()
    # TODO: 将数据库文件读取到变量中
    with open(sys.argv[1], 'r') as file:
         #csv.DictReader()将 csv 文件中的每行数据转换成一个字典.字典的键由文件的第一行(即列名)决定,对应的值来自于该行的其他部分
         reader = csv.DictReader(file)
         data = list(reader)

    # TODO: 将DNA序列文件读取到变量中
    with open(sys.argv[2], 'r') as file:
        #file.read() 方法将读取文件的全部内容,并存储到 seq 变量中
        seq = file.read()

    # TODO: 找到DNA序列中每个短串的最长匹配
    STR = []
    #reader.fieldnames 是 Python 的 csv 模块中 DictReader 对象的一个属性.它返回 csv 文件第一行的字段名列表
    for i in range(1, len(reader.fieldnames)):
        STR.append(longest_match(seq, reader.fieldnames[i]))
    # TODO: 在数据库中检查匹配的配置文件
    for i in range(len(data)):
        matches = 0
        for j in range(1, len(reader.fieldnames)):
            if int(data[i][reader.fieldnames[j]]) == STR[j - 1]:
                matches += 1
            if matches == len(reader.fieldnames) - 1:
                print(data[i]['name'])
                return
    print('No match')


def longest_match(sequence, subsequence):
    """返回序列中子序列的最长连续匹配长度."""

    # 初始化变量
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # 检查序列中的每个字符以找出子序列的最长连续匹配
    for i in range(sequence_length):
        # 初始化连续匹配的计数
        count = 0

        # 检查序列内一个"子字符串"(字符集合)中是否有子序列的匹配
        # 如果有匹配,将子字符串移动到序列中下一个可能的匹配位置
        # 继续移动子字符串并检查匹配,直到没有连续匹配为止
        while True:
            # 调整子字符串开始和结束的位置
            start = i + count * subsequence_length
            end = start + subsequence_length

            # 如果在子字符串中有匹配
            if sequence[start:end] == subsequence:
                count += 1

            # 如果在子字符串中没有匹配
            else:
                break

        # 更新找到的最长连续匹配长度
        longest_run = max(longest_run, count)

    # 在序列中的每个字符处检查匹配后,返回找到的最长连续匹配长度
    return longest_run

main()
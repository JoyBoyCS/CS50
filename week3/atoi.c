#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// 定义将字符串转为整数的函数,只需输入的字符串作为参数
int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    // 检查每个字符,确保它们都是数字
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // 将字符串转换为整数
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // 计算输入字符串的长度
    int len = strlen(input);
    long num = 0;
    // 基本情况:如果字符串为空(长度为0),则返回0
    if (len == 0)
    {
        return 0;
    }

    // 创建一个新的字符串,该字符串是原始字符串去除最后一个字符后的剩余部分
    char rinput[len];
    strncpy(rinput, input, len - 1);
    rinput[len - 1] = '\0';

    // 计算最后一个字符对应的数字,并递归地调用该函数,剩余字符串作为新的输入
    // 将递归得到的结果乘以10(因为进位),并加上当前处理的这一位的值
    num = convert(rinput) * 10 + input[len - 1] - '0';
    return num;
}
#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// 分配给字母表中每个字母的分数
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // 获取两位玩家的输入单词
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // 计算两个单词的分数
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: 打印胜者
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: 计算并返回字符串的分数
    int sum = 0;
    int index;//存储POINTS[]的索引
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isupper(word[i])) // 如果是大写字母
        {
            index = word[i] - 'A';//写成A增加可读性
            sum += POINTS[index];
        }
        else if (islower(word[i])) // 如果是小写字母
        {
            index = word[i] - 'a';//写成a增加可读性
            sum += POINTS[index];
        }
        // else
        // {
        //     sum = sum + 0;
        // }
        // sum += POINTS[index];
        /*当 word[i] 是非字母字符时，程序会跳过两个 if 条件，执行 else 分支，
        将 sum 增加 0（这本身没问题）。但是，在 else 分支之后，代码又执行了 sum += POINTS[index]; 这行。
        因为此时 index 变量并未被赋新值，所以它可能保留了前一次循环的值，
        也可能是个未定义的值（如果到目前为止 index 还未被赋值过）。这就是错误所在*/
    }
    return sum;
}

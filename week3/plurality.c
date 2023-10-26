#include <cs50.h>
#include <stdio.h>
#include <string.h>

// 候选人最大数量
#define MAX 9

// 候选人具有姓名和投票数
typedef struct
{
    string name;
    int votes;
}
candidate;

// 候选人数组
candidate candidates[MAX];

// 候选人数量
int candidate_count;

// 函数原型
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // 检查无效使用
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // 填充候选人数组
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // 遍历所有投票者
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // 检查无效投票
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // 显示选举的赢家
    print_winner();
}

// 更新新投票的总投票数
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    // 如果遍历了所有的候选人都没有找到,那么返回 false
    return false;
}

// 打印选举的赢家(或赢家们)
void print_winner(void)
{
    int max_votes = 0;

    // 查找最大投票数
    //之前写了个排序,其实人少的情况下直接找最大值就行了
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    }

    // 打印得票数为最大值的候选人
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_votes)
        {
            printf("%s\n",candidates[i].name);
        }
    }

    return;
}

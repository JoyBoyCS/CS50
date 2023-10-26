#include <cs50.h>
#include <stdio.h>
#include <string.h>

// 最大选民和候选人数量
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] 是 voter i 的第 j 名喜欢的候选人
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// 候选人有名称,投票计数,淘汰状态
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// 候选人数组
candidate candidates[MAX_CANDIDATES];

// 选民和候选人数量
int voter_count;
int candidate_count;

// 函数原型
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // 检查无效使用
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // 填充候选人数组
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("最大候选人数量为 %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("选民数量: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("最大选民数量为 %i\n", MAX_VOTERS);
        return 3;
    }

    // 继续查询投票
    for (int i = 0; i < voter_count; i++)
    {

        // 查询每个排名
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // 记录投票,除非它无效
            if (!vote(i, j, name))
            {
                printf("无效的投票.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // 继续举行淘汰赛直到存在赢家
    while (true)
    {
        // 计算给剩余候选人的票数
        tabulate();

        // 检查选举是否已经赢得
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // 淘汰最后一位候选人
        int min = find_min();
        bool tie = is_tie(min);

        // 如果平局,所有人都赢
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // 淘汰任何以最小票数的候选人
        eliminate(min);

        // 投票计数重置为零
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// 如果投票有效,则记录偏好
bool vote(int voter, int rank, string name)
{
    // 待完成
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i; //记录输入名字在候选人里面的索引
            return true;
        }
    }

    return false;
}

// 计算非淘汰候选人的票数
void tabulate(void)
{
    // 待完成
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            //前面两端代码会依次遍历所有已经被投票的候选人,如果第一顺位被淘汰就继续往下找,
            //找到第二顺位,如果没被淘汰,这个人就加1票,然后跳出循环不在找第三顺位
            if (!candidates[preferences[i][j]].eliminated)
            {
                    candidates[preferences[i][j]].votes++;
                    break;
            }
        }
    }

    return;
}

// 打印选举的赢家,如果有的话
bool print_winner(void)
{
    // 待完成
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n",candidates[i].name);
            return true;
        }
    }
    return false;
}

// 返回任何剩余候选人的最少票数
int find_min(void)
{
    // 待完成
    int min = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            if (candidates[i].votes <= min)
            {
                min = candidates[i].votes;
            }
        }

    }
    return min;
}

// 如果所有候选人之间的选举是平局,则返回 true,否则返回 false
bool is_tie(int min)
{
    // 待完成
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            if (candidates[i].votes != min)
            {
                return false;
            }
        }
    }
    return true;
}

// 淘汰最后一名的候选人(或候选人)
void eliminate(int min)
{
    // 待完成
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            if (candidates[i].votes == min)
            candidates[i].eliminated = true;
        }
    }
    return;
}
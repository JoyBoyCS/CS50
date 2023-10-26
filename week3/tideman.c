#include <cs50.h>
#include <stdio.h>
#include <string.h>

// 候选人最大数量
#define MAX 9

// preferences[i][j] 表示有多少选民更喜欢候选人i而不是j
int preferences[MAX][MAX];

// locked[i][j] 表示候选人i在图中锁定超过候选人j
bool locked[MAX][MAX];

// 每对候选人都有一个胜者和败者
typedef struct
{
    int winner;
    int loser;
}
pair;

// 候选人数组
string candidates[MAX];
//每一个元素都可以和除了自己外的其他元素形成一对.这会产生n * (n - 1)个配对
//如果不考虑顺序,如(A,B)和(B,A)是同一对所以我们需要将总数除以2
//之前想到的是阶乘,(MAX - 1)!
pair pairs[MAX * (MAX - 1) / 2];


int pair_count;
int candidate_count;

// 函数原型
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool has_cycles(int loser, int winner);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // 检查是否有无效输入
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // 清除已经锁定配对的图
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // 查询投票
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] 是选民的第i个偏好
        int ranks[candidate_count];

        // 询问每一位候选人的排名
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// 更新排名给出一个新的投票
bool vote(int rank, string name, int ranks[])
{
    // 待完成
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name,candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// 根据一名选民的排名更新偏好
void record_preferences(int ranks[])
{
    // 待完成
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;    //第一次写的时候没写++,没有增加数量
        }
    }

    return;
}

// 记录一对候选人,其中一方优于另一方
void add_pairs(void)
{
    // 待完成
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }

    return;
}

// 按胜利强度降序排列配对
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            // 计算当前配对和下一个配对的胜利强度
            int num1 = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            int num2 = preferences[pairs[j+1].winner][pairs[j+1].loser] - preferences[pairs[j+1].loser][pairs[j+1].winner];

            // 如果当前配对的胜利强度小于下一个配对的胜利强度,则交换它们
            if (num1 < num2)
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j+1];
                pairs[j+1] = temp;
            }
        }
    }
}
bool has_cycles(int loser, int winner)
{
    if (loser == winner)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (has_cycles(i, winner))
            {
                return true;
            }
        }
    }

    return false;
}
// 在候选人图中按顺序锁定配对,不形成循环
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // 如果添加这条边不会形成循环,则添加它
        if (!has_cycles(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// 打印选举的胜者
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        //要确保没有人指向i才行,之前写代码碰见一个人没指向他就结束了,要这样才能判断全部的人都没指向他
        bool is_winner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i]) // 有任何人指向候选人i,则他不能是胜利者
            {
                is_winner = false;//一旦有一个人指向了i,这里就变成了false,退出循环
                break;
            }
        }

        if (is_winner) // 如果没有任何人指向候选人i,则他是胜利者
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }

    printf("No winner found.\n");
    return;
}

// 模拟血型遗传

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 每个人都有两个亲代和两个等位基因
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

// 函数原型声明
person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // 初始化随机数生成器
    srand(time(0));

    // 创建一个具有三代人的新家庭
    person *p = create_family(GENERATIONS);

    // 打印血型家谱树
    print_family(p, 0);

    // 释放内存
    free_family(p);
}

// 创建一个新的个体,参数为 `generations`
person *create_family(int generations)
{
    // TODO: 为新人分配内存
    person *p = malloc(sizeof(person));

    // 如果还需要创建更多的后代
    if (generations > 1)
    {
        // 通过递归调用 create_family 为当前人创建两个新的父母
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // TODO: 设置当前人的父母指针
        p->parents[0] = parent0;
        p->parents[1] = parent1;
        // TODO: 根据父母的等位基因随机指定当前人的等位基因
        p->alleles[0] = parent0->alleles[rand() % 2];
        p->alleles[1] = parent1->alleles[rand() % 2];
    }

    // 如果没有更多的后代需要创建
    else
    {
        // TODO: 将父母指针设为 NULL
        p->parents[0] = NULL;
        p->parents[1] = NULL;

        // TODO: 随机指定等位基因
        p->alleles[0] = random_allele();
        p->alleles[1] = random_allele();

    }

    // TODO: 返回新创建的人
    return p;
}

// 释放 `p` 和 `p` 的所有祖先所占用的内存.
void free_family(person *p)
{
    // TODO: 处理基本情况
    if (p == NULL)
    {
        return;
    }

    // TODO: 递归地释放父母的内存
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // TODO: 释放孩子的内存
    free(p);

}

// 打印每个家庭成员及其等位基因.
void print_family(person *p, int generation)
{
    // 处理基本情况
    if (p == NULL)
    {
        return;
    }

    // 打印缩进
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // 打印人
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // 打印当前代的父母
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// 随机选择一个血型等位基因.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
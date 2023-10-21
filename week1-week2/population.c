#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // 待办事项：确定开始的尺寸

    long startsize;
    do
    {
        startsize = get_long("请输入开始数量：");
    }
    while (startsize < 9);

    // 待办事项：确定结束的尺寸
    long endsize;
    do
    {
        endsize = get_long("请输入结束数量：");
    }
    while (endsize < startsize);

    // 待办事项：计算我们达到阈值需要的年数

    long years =0;
    while ( startsize < endsize)
    {
        startsize = startsize+startsize/3-startsize/4;
        years++;
    }

    // 待办事项：打印年数
    printf("Years: %li\n", years);
}

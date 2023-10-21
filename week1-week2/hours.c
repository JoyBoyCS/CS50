#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);    //根据回答数值，填入数组
    }

    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));//把输入的小写也转成大写
    }
    while (output != 'T' && output != 'A');   //如果不是T或者A就无限循环让你输入

    printf("%.1f hours\n", calc_hours(hours, weeks, output));   //保留一位小数打印结果
}

// 待办：完成 calc_hours 函数
float calc_hours(int hours[], int weeks, char output)
{
    float avg = 0;
    float sum = 0;

    for (int i = 0; i < weeks; i++)
    {
        sum = hours[i] + sum; //求和
    }

    if ( output == 'T') //C语言中单字符必须用单引号！！！  ''
    {
        return sum;
    }
    else if (output == 'A')
    {
        avg = sum/weeks;    //求平均   之前sum的值没传进来
        return avg;
    }
    return 0;
}
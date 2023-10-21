#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // 询问客户欠多少美分
    int cents = get_cents();

    // 计算应给顾客多少个25美分的硬币
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // 计算应给顾客多少个10美分的硬币
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // 计算应给顾客多少个5美分的硬币
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // 计算应给顾客多少个1美分的硬币
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // 汇总硬币数目
    int coins = quarters + dimes + nickels + pennies;

    // 打印应给顾客的总硬币数目
    printf("%i\n", coins);
}

int get_cents(void)
{
    // 待办事项
    int cents;
    do
    {
    cents = get_int("Change owed:");
    }
    while (cents < 1);
    return cents;
}

int calculate_quarters(int cents)
{
    // TODO
    int quarters = 0;
     while (cents >= 25)
    {
        cents = cents-25;
        quarters++;
    }
    return quarters;
}

int calculate_dimes(int cents)
{
     // TODO
    int dimes = 0;
     while (cents >= 10)
    {
        cents = cents-10;
        dimes++;
    }
    return dimes;
}

int calculate_nickels(int cents)
{
     // TODO
    int nickels = 0;
     while (cents >= 5)
    {
        cents = cents-5;
        nickels++;
    }
    return nickels;
}

int calculate_pennies(int cents)
{
     // TODO
    int pennies = 0;
     while (cents >= 1)
    {
        cents = cents-1;
        pennies++;
    }
    return pennies;
}

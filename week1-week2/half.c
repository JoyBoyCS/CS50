// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include <cs50.h>
#include <stdio.h>

float half(float bill, float tax, int tip);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    int tip_percent = get_int("Tip percent: ");

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

// TODO: Complete the function
// 完成函数实现
float half(float bill, float tax, int tip)
{
    // 首先计算税款
    double total_with_tax = bill * (1 + (double)tax / 100);

    // 然后计算含税账单上的小费
    double total_with_tax_and_tip = total_with_tax * (1 + (double)tip / 100);

   // 最后返回含税及小费账单的一半
    return total_with_tax_and_tip / 2;
}
// 使用结构体进行练习
// 编写线性搜索函数进行练习

/**
 * Beach Burger Shack 的菜单上有以下 10 项
 * 汉堡: $9.5
 * 素食汉堡: $11
 * 热狗: $5
 * 起士热狗: $7
 * 炸薯条: $5
 * 起士炸薯条: $6
 * 冷压果汁: $7
 * 冷萃咖啡: $3
 * 水: $2
 * 汽水: $2
*/

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// 菜单项目数量
// 根据下面输入的项目数调整这个值(10)
#define NUM_ITEMS 4

// 菜单项目有项目名称和价格
typedef struct
{
    string item;
    float price;
}
menu_item;

// 菜单项目数组
menu_item menu[NUM_ITEMS];

// 添加项目到菜单
void add_items(void);

// 计算总成本
float get_cost(string item);

int main(void)
{
    add_items();

    printf("\n欢迎来到Beach Burger Shack!\n");
    printf("从以下菜单中选择要点的食物.完成后按回车.\n\n");

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        printf("%s: $%.2f\n", menu[i].item, menu[i]. price);
    }
    printf("\n");

    float total = 0;
    while (true)
    {
        string item = get_string("输入食物名称:");
        if (strlen(item) == 0)
        {
            printf("\n");
            break;
        }

        total += get_cost(item);
    }

    printf("你的总成本是: $%.2f\n", total);
}

// 将至少前四个项目添加到菜单数组
void add_items(void)
{
    //更简单的创建数组
    string items[] = {"Burger", "Vegan Burger", "Hot Dog", "Cheese Dog"};
    float prices[] = {9.50, 11.00, 5.00, 7.00};

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        menu[i].item = items[i];
        menu[i].price = prices[i];
    }

    return;
}
// 在菜单数组中搜索一个项目的成本
float get_cost(string item)
{
    float sum = 0;
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        if (strcmp(item,menu[i].item) == 0)
        {
            //sum = sum + menu[i].price;  仅返回价格就行了,上面有计算
            return menu[i].price;
        }
    }
    printf("Sorry, we could not find that item: %s\n", item); //找不到的话提示一下
    return 0.0f;    // 如果找不到项目,返回价格为0
}
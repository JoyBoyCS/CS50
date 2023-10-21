#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int Height;
    do
    {
        Height = get_int("请输入1-8之间的正整数：");
    }
    while (Height > 8 || Height < 1);

    for (int i = 0; i < Height; i++)
    {
        for (int j = 0; j < Height; j++)
        {
            if ( j < Height - i- 1 )
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}
#include <cs50.h>
#include <stdio.h>
#include <string.h>

void replace(string str);

int main (int argc, string argv[])
{
    if (argc == 2)
    {
        replace(argv[1]);
        printf("%s\n", argv[1]);
    }
    else
    {
        printf("您的输出有误，只能输入一个单词\n");
    }

    return 0;
}


void replace(string str)
{
    for(int i = 0, n = strlen(str); i < n; i++)
    {
        if (str[i] == 'a')
        {
            str[i] = '6';
        }
        else if (str[i] == 'e')
        {
            str[i] = '3';
        }
        else if (str[i] == 'i')
        {
            str[i] = '1';
        }
        else if (str[i] == 'o')
        {
            str[i] = '0';
        }
    }
}
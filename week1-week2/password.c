// 检查密码是否至少包含一个小写字母，大写字母，数字和符号
// 练习遍历字符串
// 掌握使用ctype库
#include <string.h>
#include <ctype.h>
#include <cs50.h>
#include <stdio.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    //之前的写法有问题，是对每个字符进行遍历，找到错误直接返回了false，这样会导致没检查完就结束了，要这样赋值
    bool has_uppercase = false, has_lowercase = false, has_digit = false, has_symbol = false;

    for(int i = 0; i < strlen(password); i++)
    {
        //不为0就是包含，然后就会赋值为trun
        if (isupper(password[i]))
        {
            has_uppercase = true;
        }
        else if (islower(password[i]))
        {
            has_lowercase = true;
        }
        else if (isdigit(password[i]))
        {
            has_digit = true;
        }
        else if (ispunct(password[i]))
        {
            has_symbol = true;
        }
    }

    //以上都满足，最终返回true
    if(has_uppercase && has_lowercase && has_digit && has_symbol)
    {
        return true;
    }
    else
    {
        return false;
    }
}
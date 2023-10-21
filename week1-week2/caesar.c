#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string Get_ciphertext(string argv,string plaintext);

int main(int argc, string argv[])
{
    bool flag = true;
    if (argc == 2)
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isdigit(argv[1][i]) == 0)  //isdigit 只能检查单个字符是否是数字，不能检查字符串
            {
                flag = false;
                return 1;
            }
        }
        if (flag == true) //最后判断的时候要用==不能用=
            {
                string plaintext = get_string("plaintext: ");
                string ciphertext = Get_ciphertext(argv[1],plaintext); //函数跟变量名字不能一样
                printf("ciphertext: %s\n",ciphertext);
            }
     }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
  }
string Get_ciphertext(string argv,string plaintext)
{
    int sum = 0;
    //int k = (int)argv;  //不能直接把字符串转换成int
    for (int i = 0, n = strlen(argv); i < n; i++)
    {
        argv[i] = (int)argv[i] -48; //把字符转化成他的ASCII码，然后再减去48就是对应的数字
        sum = sum +argv[i];
        sum = sum * 10;
    }
    int k = sum / 10;
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isupper(plaintext[i]) != 0)
        {
            plaintext[i] = (plaintext[i] - 65 + k) % 26 + 65;
        }
        else if (islower(plaintext[i]) != 0)
        {
            plaintext[i] = (plaintext[i] - 97 + k) % 26 + 97;
        }
        else
        {
            plaintext[i] = plaintext[i];
        }
    }
    return plaintext;
}
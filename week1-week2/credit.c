#include <cs50.h>
#include <stdio.h>

long  get_number (void);
int length (long number);
string judgment(long number,int len);

int main(void)
{
    long number = get_number(); //得把返回值赋值才行

    int len = length(number); //得把返回值赋值才行

    string answer =  judgment(number,len);

    printf("%s\n",answer);
}

long  get_number (void)
{
    long number;
    do
    {
    number = get_long("Number: ");
    }
    while (number < 1);
    return number;
}

int length (long number)
{
    int len = 0;
    while (number > 0)
    {
        number = number / 10;
        len++;
    }
    return len;
}

string judgment(long number,int len)
{
    long x1 = number / 10;   //从倒数第二个数字开始取模，这里先减少一位
    long x2 = number;
    int sum = 0;  //求和
    int y1;  //取模后的余数
    int y2;
    while (x1 >0)
    {
        y1 =  x1 % 10 *2;
        if (y1 < 10)
        {
            sum = sum + y1;
        }
        //大于等于10时，拆开写
        else if (y1 >= 10)   //应该大于等于10，之前少考虑了，10也是2位数
        {
            sum = sum + y1 % 10 + y1 / 10;  //可以简化成sum = sum + y % 10 + y / 10;
        }
        //间隔跳过一位数
        x1 = x1 / 100;  //之前这里写成/10，这样只能减少一位数，不能跳过
    }
        while (x2 >0)
    {
        y2 =  x2 % 10;
        sum = sum + y2;
        x2 = x2 / 100;
    }
        string answer = "INVALID";

        if (len == 13 && sum % 10 == 0 && number / (len -1) == 4)
        {
            answer = "VISA";
        }
        else if (len == 16 && sum % 10 == 0 && number / (len -1) == 4)
        {
            answer = "VISA";
        }
        else if ( len == 16)
        {
            if(sum % 10 == 0 )
            {
                if ( 50 < number/(len -2) && number/(len -2) < 56)    //不能大于...小于...得用&&或者||
                {
                    answer = "MASTERCARD";
                }
            }
        }
          else if ( len == 15)
        {
            if(sum % 10 == 0)
            {
                if  (number/(len -2)== 34 ||  number/(len -2) == 37)
                {
                    answer = "AMEX";
                }
            }
        }
        else
        {
            answer = "INVALID";
        }
    return answer;
}


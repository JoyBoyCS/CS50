#include <cs50.h>
#include <stdio.h>
#include <string.h>

void conversion (string Message);

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    string Message = get_string("Message: ");
    conversion (Message);

}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}

void conversion (string Message)
{
    for (int i = 0, n = strlen(Message); i < n; i++)
    {
        int array[BITS_IN_BYTE] = {0};
        for (int j = BITS_IN_BYTE -1; j >= 0; j--) //要减1，数组最后一个下标是 n-1
        {
            array[j] = Message[i] % 2;
            Message[i] = (int)Message[i] / 2;
        }
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            print_bulb(array[j]);   //淦之前给想复杂了，忘了调用这个东西了，不需要储存到多个数组中了，直接打印就行
        }
        printf("\n");
    }
}
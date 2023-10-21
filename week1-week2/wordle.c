#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

//每个文本文件包含1000个单词
#define LISTSIZE 1000

//颜色和得分的值（EXACT == 正确的字母，正确的位置；CLOSE == 正确的字母，错误的位置；WRONG == 错误的字母）
#define EXACT 2
#define CLOSE 1
#define WRONG 0

//用于标注文字的ANSI颜色代码
#define GREEN   "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW  "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED     "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET   "\e[0;39m"

//用户自定义函数原型
string get_guess(int wordsize);
int check_word(string guess, int wordsize, int status[], string choice);
void print_word(string guess, int wordsize, int status[]);

int main(int argc, string argv[])
{
    //确保使用方法正确
    //TODO #1
    if (argc != 2)
    {
        printf("Usage: ./wordle wordsize\n");
        return 1;
    }

    int wordsize = 0;

    //确保argv[1]是5，6，7或8，并将该值存储在wordsize中
    //TODO #2
    if (argc == 2)
    {
        //不能直接argv[1] == "5"这样进行比较，在C中，不能直接使用 == 操作符来比较字符串
        if (strcmp(argv[1], "5") == 0 || strcmp(argv[1], "6") == 0 || strcmp(argv[1], "7") == 0 || strcmp(argv[1], "8") == 0)
        {
            wordsize = atoi(argv[1]); //这里把字符串转换成整数
        }
        else
        {
            printf("Error: wordsize must be either 5, 6, 7, or 8\n");
        }
    }

    //打开正确的文件，每个文件有正好LISTSIZE个单词
    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        return 1;
    }

    //把词表文件读入一个大小为LISTSIZE的数组
    char options[LISTSIZE][wordsize + 1]; //“+1” 是为了存储字符串结束符 ‘\0’

    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    //用伪随机算法选择一个游戏单词
    srand(time(NULL)); //根据当前时间，产生一个随机数
    //rand() 是一个 C 标准库函数，它生成一个伪随机数，范围在 0 到 RAND_MAX 之间;
    //a % b 会返回 a 除以 b 的余数。因此，rand() % LISTSIZE 产生的是一个在 0 到 LISTSIZE - 1 之间的随机整数
    //如果 LISTSIZE 是 10，那么 rand() % LISTSIZE 就会生成一个在 0 到 9 之间的随机整数。这个随机整数可以用作数组索引，从而实现从数组中随机选择一个元素
    string choice = options[rand() % LISTSIZE]; //choice是被随机选中的字符串

    //允许猜测的次数比单词长度多一次
    int guesses = wordsize + 1;
    bool won = false;

    //打印欢迎信息，使用ANSI颜色代码进行演示
    printf(GREEN"This is WORDLE50"RESET"\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);

    //主游戏循环，每次猜一次
    for (int i = 0; i < guesses; i++)
    {
        //获取用户的猜测
        string guess = get_guess(wordsize);

        //用于保存猜测状态的数组，初始设置为0
        int status[wordsize];

        //将状态数组的所有元素初始化为0，即WRONG
        //TODO #4
        for (int j = 0; j < wordsize; j++)
        {
            status[j] = 0;
        }

        //计算猜测得分
        int score = check_word(guess, wordsize, status, choice);

        printf("Guess %i: ", i + 1);

        //打印猜测结果
        print_word(guess, wordsize, status);

        //如果他们完全猜对了，就终止循环
        if (score == EXACT * wordsize)
        {
            won = true;
            break;
        }
    }

    //打印游戏结果
    //TODO #7
    if (won == true) //比较要用 == 又错了一次！！！
    {
        printf("You won!\n");
    }
    else if (guesses == wordsize + 1)
    {
        printf("is %s\n",choice);
    }

    //一切到此结束！
    return 0;
}

string get_guess(int wordsize)
{
    string guess = "";

    //确保用户真的提供了一个正确长度的猜测
    //TODO #3
    int lower;
    do
    {
        guess = get_string("Input a %i-letter word: ",wordsize);
        int n = strlen(guess);

        lower = 1; //用来检查是否全是小写字母
        for (int i = 0; i < n; i++)
        {
            if (!islower(guess[i]))
            {
                lower = 0; //用lower做标记，如果不是小写的字母，lower会变成0，最后while检查这个值来判断是否是小写
                break;
            }
        }
    }
    while(strlen(guess) != wordsize || lower == 0);
    return guess;
}

int check_word(string guess, int wordsize, int status[], string choice)
{
    int score = 0;

    //比较猜测和选项，根据情况给分，将得分存储在状态中
    //TODO #5

    //提示
    //遍历猜测中的每个字母:guess
    for (int i = 0; i < wordsize; i++)
    {
        //遍历选择中的每个字母:choice
        for(int j = 0; j < wordsize; j++)
        {
            //比较当前猜测字母和当前选择字母
            //如果它们在单词中的位置相同，得EXACT分（绿色），并且跳出，这样你就不会再比较那个字母了
            if (guess[i] == choice[j] && i == j)
            {
                status[i] = EXACT;
                break;
            }
            //如果它在词中，但位置不对，得CLOSE分（黄色）
            else if (guess[i] == choice[j] && i != j)
            {
                status[i] = CLOSE;
                break;
            }
        }
    }
        //通过添加上述每个字母的得分来跟踪总得分
        for (int i = 0; i < wordsize; i++)
        {
            score  += status[i];
        }
    return score;
}

void print_word(string guess, int wordsize, int status[])
{
    //按照正确的颜色编码逐个打印单词，然后将终端字体重置为正常
    //TODO #6
    for (int i = 0; i < wordsize; i++)
    {
        if (status[i] == EXACT)
        {
            printf(GREEN"%c"RESET,guess[i]);
        }
        else if (status[i] == CLOSE)
        {
            printf(YELLOW"%c"RESET,guess[i]); //字符用%c
        }
        else
        {
            printf(RED"%c"RESET,guess[i]);
        }
    }

    printf("\n");
    return;
}
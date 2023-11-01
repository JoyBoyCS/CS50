#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>

#include "dictionary.h"

// 表示哈希表中的一个节点
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: 在哈希表中选择桶的数量
const unsigned int N = 144011;

int word_count = 0;

// 哈希表
node *table[N];

// 如果单词在字典中,返回true,否则返回false
bool check(const char *word)
{
    int num = hash(word);
    node *n = table[num];
    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
        n = n->next;
    }
    return false;
}
// 将单词哈希到一个数字
unsigned int hash(const char *word)
{
    int sum = 0;
    int n = strlen(word);

    for (int i = 0; i < n; i++)
    {
        sum += tolower((unsigned char)word[i]) * (i + 1);
    }

    return (sum * n) % N;
}

// 将字典加载到内存,如果成功返回true,否则返回false
bool load(const char *dictionary)
{
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        printf("打开文件失败!\n");
        return false;
    }

    //table = NULL;  哈希表table[N]是一个指针数组,每个元素都是一个指向node类型的指针,因此不应设置为NULL,而且不能整体赋值
    //通过循环遍历的方式,将每个链表的头指针设置为NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char temp[LENGTH + 1];
    while(fscanf(input, "%s", temp) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        //n->word = strcpy(temp);  太久不用了,语法用错了,加深记忆一下
        strcpy(n->word, temp);
        n->next = NULL;

        //n->next = table;  跟上面一样,不能对整个哈希表直接操作
        //table = n;
        //计算单词的哈希值,得到在哈希表中的索引
        int index = hash(temp);

        n->next = table[index];
        table[index] = n;

        word_count++;
    }

    //记得关闭文件
    fclose(input);

    return true;
}

// 如果字典已经被加载,则返回字典中的单词数量,否则如果还未加载,返回0
unsigned int size(void)
{

    return word_count;
}

// 从内存中卸载字典,如果成功返回true,否则返回false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while(ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }

    return true;
}

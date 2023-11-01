// 将热门的狗名保存在 Trie 中
// https://www.dailypaws.com/dogs-puppies/dog-names/common-dog-names

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_ALPHABET 26
#define MAXCHAR 20

typedef struct node
{
    bool is_word;
    struct node *children[SIZE_OF_ALPHABET];
}
node;

// 函数原型
bool check(char *word);
bool unload(void);
void unloader(node *current);

// Trie 的根节点
node *root;

// 缓冲区,用于读取狗名
char name[MAXCHAR];

int main(int argc, char *argv[])
{
    // 检查命令行参数
    if (argc != 2)
    {
        printf("使用方法: ./trie infile\n");
        return 1;
    }

    // 包含名字的文件
    FILE *infile = fopen(argv[1], "r");
    if (!infile)
    {
        printf("打开文件错误!\n");
        return 1;
    }

    // 分配Trie的根节点
    root = malloc(sizeof(node));

    if (root == NULL)
    {
        return 1;
    }

    root->is_word = false;
    for (int i = 0; i < SIZE_OF_ALPHABET; i++)
    {
        root->children[i] = NULL;
    }

    // 将单词添加到Trie
    while (fscanf(infile, "%s", name) == 1)
    {
        node *cursor = root;

        for (int i = 0, n = strlen(name); i < n; i++)
        {
            int index = tolower(name[i]) - 'a';
            if (cursor->children[index] == NULL)
            {

                // 创建节点
                node *new = malloc(sizeof(node));
                new->is_word = false;
                for (int j = 0; j < SIZE_OF_ALPHABET; j++)
                {
                    new->children[j] = NULL;
                }
                cursor->children[index] = new;
            }

            // 转到我们可能刚刚创建的节点
            cursor = cursor->children[index];
        }

        // 如果我们在单词的末尾,标记它为一个单词
        cursor->is_word = true;
    }

    if (check(get_string("检查单词: ")))
    {
        printf("找到了!\n");
    }
    else
    {
        printf("没找到.\n");
    }

    if (!unload())
    {
        printf("释放内存有问题!\n");
        return 1;
    }

    fclose(infile);
}

// TODO: 完成 check 函数,如果找到则返回 true,没有找到则返回 false
bool check(char* word)
{
    node * cursor = root;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        int index = tolower(word[i]) - 'a';
        if (cursor->children[index] != NULL)
        {
            cursor = cursor->children[index];
        }
        else
        {
            return false;
        }

    }
    //检查是否到达了一个词的末尾
    if (cursor->is_word)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 从内存中卸载 Trie
bool unload(void)
{

    // 递归函数处理所有的释放
    unloader(root);

    return true;
}

void unloader(node* current)
{

    // 遍历所有的子节点看是否指向任何东西,并且如果他们指向了,就去那里
    for (int i = 0; i < SIZE_OF_ALPHABET; i++)
    {
        if (current->children[i] != NULL)
        {
            unloader(current->children[i]);
        }
    }

    // 在我们检查所有的子节点指向 null 后,我们就可以释放节点
    // 并返回到这个函数的前一个迭代.
    free(current);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // 检查命令行参数
    if (argc != 2)
    {
        printf("使用方法: ./read infile\n");
        return 1;
    }

    // 创建用于读取数据的缓冲区
    char buffer[7];

    // 创建数组以存储车牌号码
    char *plates[8];

    // 打开输入文件
    FILE *infile = fopen(argv[1], "r");

    // 定义索引
    int idx = 0;

    // 当从文件读取7个字符成功时,循环继续
    while (fread(buffer, 1, 7, infile) == 7)
    {
        // 将 '\n' 替换为 '\0'
        buffer[6] = '\0';

        plates[idx] = malloc(7 * sizeof(char));
        if (plates[idx] == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            return 2;
        }
        strcpy(plates[idx], buffer);
        idx++;
    }

    // 遍历并打印所有车牌号码
    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
    }
    //最后要释放内存
    for (int i = 0; i < 8; i++)
    {
        free(plates[i]);
    }
}
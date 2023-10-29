// 修改音频文件的音量

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// .wav 头部的字节数
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // 检查命令行参数
    if (argc != 4)
    {
        printf("用法: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // 打开文件并确定缩放因子
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("无法打开文件.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("无法打开文件.\n");
        return 1;
    }

    float factor = atof(argv[3]);
    uint8_t header[HEADER_SIZE];

    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    int16_t buffer;

    while (fread(&buffer, sizeof(int16_t), 1, input) == 1)
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }
    // 关闭文件
    fclose(input);
    fclose(output);
}
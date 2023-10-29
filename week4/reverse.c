#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h" // 导入wav.h头文件,此文件应包含`WAVHEADER`类型的定义

const int HEADER_SIZE = 44;
int check_format(WAVHEADER header); // 声明检查音频格式的函数
int get_block_size(WAVHEADER header); // 声明获取块大小的函数

int main(int argc, char *argv[])
{
    // 确保正确使用
    // 待完成 #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }
    if (strstr(argv[1], ".wav") == NULL || strstr(argv[2], ".wav") == NULL)
    {
        printf("Input is not a WAV file.\n");
        return 1;
    }

    // 打开输入文件进行读取
    // 待完成 #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }
    // 读取文件头
    // 待完成 #3
    WAVHEADER header;
    fread(&header, HEADER_SIZE, 1, input);

    // 使用check_format函数确保是WAV格式
    // 待完成 #4
    if (check_format(header) == 0)
    {
        printf("The file is not in valid WAV format.\n");
        return 1;
    }

    // 打开输出文件进行写入
    // 待完成 #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open %s.\n", argv[2]);
        return 1;
    }

    // 将文件头写入文件
    // 待完成 #6
    fwrite(&header, HEADER_SIZE, 1, output);

    // 使用get_block_size函数计算块的大小
    // 待完成 #7
    int block_size = get_block_size(header);

    // 将反向音频写入文件
    // 待完成 #8
    fseek(input, 0 ,SEEK_END);
    long fileSize = ftell(input);

    long lastBlockPos =fileSize -block_size;
    BYTE *buffer = malloc(sizeof(BYTE) * block_size);
    if (buffer ==NULL)
    {
        printf("处理内存分配失败\n");
        return 1;
    }
    for (long i = lastBlockPos; i >= HEADER_SIZE; i -= block_size)
    {
        fseek(input, i ,SEEK_SET);

        if(fread(buffer, block_size, 1, input) != 1)
        {
            printf("Failed to read file.\n");
            free(buffer);
            return 1;
        }

        if(fwrite(buffer, block_size, 1, output) != 1)
        {
            printf("Failed to write file.\n");
            free(buffer);
            return 1;
        }
    }

    free(buffer);

    fclose(input);
    fclose(output);

    return 0;
}

int check_format(WAVHEADER header)
{
    // 检查音频格式
    // 待完成 #4
    if (memcmp(header.chunkID, "RIFF", 4) == 0
    && memcmp(header.format, "WAVE", 4) == 0
    && memcmp(header.subchunk1ID, "fmt", 3) == 0
    && memcmp(header.subchunk2ID, "data", 4) == 0)
    {
        return 1;
    }

return 0;
}

int get_block_size(WAVHEADER header)
{
    // 获取块的大小
    // 待完成 #7
    int sample_size = header.bitsPerSample / 8;
    int block_size = header.numChannels * sample_size;

    return block_size;
}
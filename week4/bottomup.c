// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: copy infile outfile\n");
        return 1;
    }

        // 记住文件名
    char *infile = argv[1];
    char *outfile = argv[2];

    // 打开输入文件
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("无法打开 %s.\n", infile);
        return 2;
    }

    // 打开输出文件
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("无法创建 %s.\n", outfile);
        return 3;
    }

    // 读取输入文件的BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // 读取输入文件的BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // 确保输入文件可能是一个24位未压缩的BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        printf("不支持的文件格式.\n");
        return 4;
    }

    // 写入输出文件的BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // 写入输出文件的BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // 确定扫描线的填充
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    RGBTRIPLE image [abs(bi.biHeight)][bi.biWidth];

    // 遍历输入文件的扫描线
    for (int i = 0; i < abs(bi.biHeight); i++)
    {
        for (int j = 0; j < bi.biWidth; j++)
        {

            fread(&image[i][j], sizeof(RGBTRIPLE), 1, inptr);

        }

        // 如果有的话,跳过填充
        fseek(inptr, padding, SEEK_CUR);
    }

    for (int i = abs(bi.biHeight) - 1; i >=0; i--)
    {
        for (int j = 0; j < bi.biWidth; j++)
        {
            fwrite(&image[i][j],sizeof(RGBTRIPLE), 1, outptr);
        }
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // 关闭输入文件
    fclose(inptr);

    // 关闭输出文件
    fclose(outptr);

    // 成功
    return 0;
}
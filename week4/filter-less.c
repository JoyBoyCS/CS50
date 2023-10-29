#include <math.h>

#include "helpers.h"


// 将图像转换为灰度图
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //求像素的平均值,然后赋值给每个颜色
            int average =round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }

    return;
}

// 将图像转换为棕褐色调的图像(sepia)
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //在这里的时候需要直接四舍五入并且赋值,之前在if里面我没进行赋值
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// 将图像水平翻转
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //int *buffer;
    //应该给整个图像分配一个缓冲区,而不是一个像素
    RGBTRIPLE buffer[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            buffer[i][j] = image[i][j];

        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
           image[i][j] = buffer[i][width - j - 1];
        }
    }
    return;
}

// 对图像进行模糊处理
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            buffer[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double totalRed = 0, totalBlue = 0, totalGreen = 0;
            int count = 0;
            for (int a = -1; a <= 1; a++)
            {
                for(int b = -1; b <= 1; b++)
                {
                    int ni = i + a;
                    int nj = j + b;

                    if (ni >=0 && ni < height && nj >= 0 && nj < width)
                    {
                        // 如果在,累加颜色值,并增加像素计数器
                        totalRed += buffer[ni][nj].rgbtRed;
                        totalBlue += buffer[ni][nj].rgbtBlue;
                        totalGreen += buffer[ni][nj].rgbtGreen;
                        count++;
                    }
                }
            }
            image[i][j].rgbtRed = round(totalRed / count);
            image[i][j].rgbtBlue = round(totalBlue / count);
            image[i][j].rgbtGreen = round(totalGreen / count);
        }
    }

    return;
}
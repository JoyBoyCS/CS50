#include "helpers.h"
#include <math.h>

// Convert image to grayscale
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
// Reflect image horizontally
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

// Blur image
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
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
            int GxRed = 0, GxBlue = 0, GxGreen = 0;
            int GyRed = 0, GyBlue = 0, GyGreen = 0;

            for (int a = -1; a <= 1; a++)
            {
                for(int b = -1; b <= 1; b++)
                {
                    int ni = i + a;
                    int nj = j + b;

                    int x;//声明一个x系数
                    if (a != 0)
                    {
                        x = b;
                    }
                    else
                    {
                        x = b * 2;
                    }

                    int y;//声明一个y系数
                    if (b != 0)
                    {
                        y = a;
                    }
                    else
                    {
                        y = a * 2;
                    }
                    if (ni >=0 && ni < height && nj >= 0 && nj < width)
                    {
                        GxRed += buffer[ni][nj].rgbtRed * x;
                        GxBlue += buffer[ni][nj].rgbtBlue * x;
                        GxGreen += buffer[ni][nj].rgbtGreen * x;

                        GyRed += buffer[ni][nj].rgbtRed * y;
                        GyBlue += buffer[ni][nj].rgbtBlue * y;
                        GyGreen += buffer[ni][nj].rgbtGreen * y;
                    }
                }
            }
            int Red = round(sqrt(GxRed * GxRed + GyRed * GyRed));
            int Blue = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
            int Green = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));

            if (Red > 255)
            {
                Red = 255;
            }
            if (Blue > 255)
            {
                Blue = 255;
            }
            if (Green > 255)
            {
                Green = 255;
            }
            image[i][j].rgbtRed = Red;
            image[i][j].rgbtBlue = Blue;
            image[i][j].rgbtGreen = Green;
        }
    }
    return;
}

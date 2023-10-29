#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    char filename[8];
    int count = 0;
    BYTE buffer[BLOCK_SIZE];
    FILE *output = NULL;
    while(fread(&buffer, BLOCK_SIZE, 1, input))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if(output != NULL)
            {
                fclose(output);
            }

            sprintf(filename, "%03i.jpg", count);
            count++;
            output = fopen(filename, "w");
            if (output == NULL)
            {
                printf("Could not create %s.\n", filename);
                return 1;
            }
        }
        if(output != NULL)
        {
            fwrite(&buffer, BLOCK_SIZE, 1, output);
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}
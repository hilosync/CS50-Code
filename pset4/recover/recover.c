#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef uint8_t BYTE;
bool newJPGStart(BYTE buffer[]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image \n");
        return 1;
    }

    FILE *rawFile = fopen(argv[1], "r");
    if (rawFile == NULL)
    {
        printf("No file found\n");
        return 1;
    }

    BYTE buffer[512];
    FILE* output;
    int fileIndex = 0;
    bool firstImageFound = false;
    while (fread(buffer, 512, 1, rawFile))
    {
        if (newJPGStart(buffer))
        {
            if (!firstImageFound)
                firstImageFound = true;
            else
                fclose(output);

            char filename[8];
            sprintf(filename, "%03i.jpg", fileIndex++);
            output = fopen(filename, "w");
            if (output == NULL)
                return 1;
            fwrite(buffer, 512,1,output);

        }

        else if (firstImageFound)
        {
            fwrite(buffer,512,1,output);
        }

    }

    fclose(output);
    fclose(rawFile);
}

bool newJPGStart(BYTE buffer[])
{
    return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
}
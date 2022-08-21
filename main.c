#include <stdio.h>
#include "bmp.h"

int main()
{
    unsigned char *bmp;
    unsigned int width, height;
    read_bmp("img\\1.input.bmp", &bmp, &width, &height);
    for (int i = 0; i < (width * height * 3); i++)
    {
        bmp[i] = 255 - bmp[i];
    }

    save_bmp("img\\1.output.bmp", bmp, width, height);

    return 0;
}
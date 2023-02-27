#include <stdio.h>
#include "bmp.h"

int main()
{
  unsigned char *bmp;
  unsigned int width, height;
  readBmp("../img/1.input.bmp", &bmp, &width, &height);
  for (int i = 0; i < (width * height * 3); i++)
    bmp[i] = 255 - bmp[i];

  saveBmp("1.output.bmp", bmp, width, height);
  free(bmp);

  return 0;
}
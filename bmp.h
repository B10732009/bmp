#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BMP_HEADER_SIZE 14
#define BMP_INFO_HEADER_SIZE 40

int read_bmp(const char *filename, unsigned char **bmp,
             unsigned int *width, unsigned int *height);
int save_bmp(const char *filename, const unsigned char *bmp,
             const unsigned int width, const unsigned int height);

#endif
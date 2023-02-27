#include "bmp.h"

int readBmp(const char *filename, unsigned char **bmp, unsigned int *width, unsigned int *height)
{
  // open file
  FILE *fp = fopen(filename, "rb");
  if (!fp)
    return 1;

  // read width
  fseek(fp, 18, SEEK_SET);
  fread(width, sizeof(unsigned int), 1, fp);

  // read height
  fseek(fp, 22, SEEK_SET);
  fread(height, sizeof(unsigned int), 1, fp);

  // padding size
  unsigned int paddingSize = (4 - ((*width) * 3) % 4) % 4;

  // read data offset
  fseek(fp, 10, SEEK_SET);
  unsigned int dataOffset;
  fread(&dataOffset, sizeof(unsigned int), 1, fp);

  // start reading pixels
  fseek(fp, dataOffset, SEEK_SET);
  (*bmp) = (unsigned char *)malloc((*width) * (*height) * 3 * sizeof(unsigned char));
  for (int i = 0; i < (*height); i++)
  {
    // read pixels
    fread((*bmp) + ((*width) * 3 * i), sizeof(unsigned char), (*width) * 3, fp);

    // jump over padding bytes
    fseek(fp, paddingSize, SEEK_CUR);
  }

  // close file
  fclose(fp);
  return 0;
}

int saveBmp(const char *filename, const unsigned char *bmp, const unsigned int width, const unsigned int height)
{
  // header and information header
  unsigned char header[BMP_HEADER_SIZE];
  unsigned char infoHeader[BMP_INFO_HEADER_SIZE];

  // padding
  unsigned char padding[3];
  unsigned int paddingSize = (4 - (width * 3) % 4) % 4;

  // file size and data offset
  unsigned int filesize = BMP_HEADER_SIZE + BMP_INFO_HEADER_SIZE + (width * height * 3) + (paddingSize * height);
  unsigned int dataOffset = BMP_HEADER_SIZE + BMP_INFO_HEADER_SIZE;

  // initialize
  memset(header, 0, BMP_HEADER_SIZE);
  memset(infoHeader, 0, BMP_INFO_HEADER_SIZE);
  memset(padding, 0, 3);

  // signature
  header[0] = 'B';
  header[1] = 'M';

  // file size
  header[2] = filesize & 0xff;
  header[3] = (filesize >> 8) & 0xff;
  header[4] = (filesize >> 16) & 0xff;
  header[5] = (filesize >> 24) & 0xff;

  // reserved
  /*
  header[6] = 0;
  header[7] = 0;
  header[8] = 0;
  header[9] = 0;
  */

  // data offset
  header[10] = dataOffset & 0xff;
  header[11] = (dataOffset >> 8) & 0xff;
  header[12] = (dataOffset >> 16) & 0xff;
  header[13] = (dataOffset >> 24) & 0xff;

  // info header size
  infoHeader[0] = BMP_INFO_HEADER_SIZE & 0xff;
  infoHeader[1] = (BMP_INFO_HEADER_SIZE >> 8) & 0xff;
  infoHeader[2] = (BMP_INFO_HEADER_SIZE >> 16) & 0xff;
  infoHeader[3] = (BMP_INFO_HEADER_SIZE >> 24) & 0xff;

  // width
  infoHeader[4] = width & 0xff;
  infoHeader[5] = (width >> 8) & 0xff;
  infoHeader[6] = (width >> 16) & 0xff;
  infoHeader[7] = (width >> 24) & 0xff;

  // height
  infoHeader[8] = height & 0xff;
  infoHeader[9] = (height >> 8) & 0xff;
  infoHeader[10] = (height >> 16) & 0xff;
  infoHeader[11] = (height >> 24) & 0xff;

  // planes
  infoHeader[12] = 1;
  infoHeader[13] = 0;

  // bits per pixel
  infoHeader[14] = 24;
  infoHeader[15] = 0;

  // compression
  /*
  infoHeader[16] = 0;
  infoHeader[17] = 0;
  infoHeader[18] = 0;
  infoHeader[19] = 0;
  */

  // image size (compressed)
  /*
  infoHeader[20] = 0;
  infoHeader[21] = 0;
  infoHeader[22] = 0;
  infoHeader[23] = 0;
  */

  // x PPM
  /*
  infoHeader[24] = 0;
  infoHeader[25] = 0;
  infoHeader[26] = 0;
  infoHeader[27] = 0;
  */

  // y PPM
  /*
  infoHeader[28] = 0;
  infoHeader[29] = 0;
  infoHeader[30] = 0;
  infoHeader[31] = 0;
  */

  // color used
  /*
  infoHeader[32] = 0;
  infoHeader[33] = 0;
  infoHeader[34] = 0;
  infoHeader[35] = 0;
  */

  // important colors
  /*
  infoHeader[36] = 0;
  infoHeader[37] = 0;
  infoHeader[38] = 0;
  infoHeader[39] = 0;
  */

  // open file
  FILE *fp = fopen(filename, "wb");

  // write header and information header
  fwrite(header, sizeof(unsigned char), BMP_HEADER_SIZE, fp);
  fwrite(infoHeader, sizeof(unsigned char), BMP_INFO_HEADER_SIZE, fp);

  // start writing pixels
  for (int i = 0; i < height; i++)
  {
    // write pixels
    fwrite(bmp + (width * 3 * i), sizeof(unsigned char), (width * 3), fp);

    // write padding
    fwrite(padding, sizeof(unsigned char), paddingSize, fp);
  }

  // close file
  fclose(fp);
  return 0;
}

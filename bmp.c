#include "bmp.h"

int read_bmp(const char *filename, unsigned char **bmp,
             unsigned int *width, unsigned int *height)
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
    unsigned int padding_size = (4 - ((*width) * 3) % 4) % 4;

    // read data offset
    fseek(fp, 10, SEEK_SET);
    unsigned int data_offset;
    fread(&data_offset, sizeof(unsigned int), 1, fp);

    // start reading pixels
    fseek(fp, data_offset, SEEK_SET);
    (*bmp) = (unsigned char *)malloc((*width) * (*height) * 3 * sizeof(unsigned char));
    for (int i = 0; i < (*height); i++)
    {
        // read pixels
        fread((*bmp) + ((*width) * 3 * i), sizeof(unsigned char), (*width) * 3, fp);

        // jump over padding bytes
        fseek(fp, padding_size, SEEK_CUR);
    }

    // close file
    fclose(fp);
    return 0;
}

int save_bmp(const char *filename, const unsigned char *bmp,
             const unsigned int width, const unsigned int height)
{
    // header and information header
    unsigned char header[BMP_HEADER_SIZE];
    unsigned char info_header[BMP_INFO_HEADER_SIZE];

    // padding
    unsigned char padding[3];
    unsigned int padding_size = (4 - (width * 3) % 4) % 4;

    // file size and data offset
    unsigned int filesize = BMP_HEADER_SIZE + BMP_INFO_HEADER_SIZE +
                            (width * height * 3) + (padding_size * height);
    unsigned int data_offset = BMP_HEADER_SIZE + BMP_INFO_HEADER_SIZE;

    // initialize
    memset(header, 0, BMP_HEADER_SIZE);
    memset(info_header, 0, BMP_INFO_HEADER_SIZE);
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
    header[10] = data_offset & 0xff;
    header[11] = (data_offset >> 8) & 0xff;
    header[12] = (data_offset >> 16) & 0xff;
    header[13] = (data_offset >> 24) & 0xff;

    // info header size
    info_header[0] = BMP_INFO_HEADER_SIZE & 0xff;
    info_header[1] = (BMP_INFO_HEADER_SIZE >> 8) & 0xff;
    info_header[2] = (BMP_INFO_HEADER_SIZE >> 16) & 0xff;
    info_header[3] = (BMP_INFO_HEADER_SIZE >> 24) & 0xff;

    // width
    info_header[4] = width & 0xff;
    info_header[5] = (width >> 8) & 0xff;
    info_header[6] = (width >> 16) & 0xff;
    info_header[7] = (width >> 24) & 0xff;

    // height
    info_header[8] = height & 0xff;
    info_header[9] = (height >> 8) & 0xff;
    info_header[10] = (height >> 16) & 0xff;
    info_header[11] = (height >> 24) & 0xff;

    // planes
    info_header[12] = 1;
    info_header[13] = 0;

    // bits per pixel
    info_header[14] = 24;
    info_header[15] = 0;

    // compression
    /*
    info_header[16] = 0;
    info_header[17] = 0;
    info_header[18] = 0;
    info_header[19] = 0;
    */

    // image size (compressed)
    /*
    info_header[20] = 0;
    info_header[21] = 0;
    info_header[22] = 0;
    info_header[23] = 0;
    */

    // x PPM
    /*
    info_header[24] = 0;
    info_header[25] = 0;
    info_header[26] = 0;
    info_header[27] = 0;
    */

    // y PPM
    /*
    info_header[28] = 0;
    info_header[29] = 0;
    info_header[30] = 0;
    info_header[31] = 0;
    */

    // color used
    /*
    info_header[32] = 0;
    info_header[33] = 0;
    info_header[34] = 0;
    info_header[35] = 0;
    */

    // important colors
    /*
    info_header[36] = 0;
    info_header[37] = 0;
    info_header[38] = 0;
    info_header[39] = 0;
    */

    // open file
    FILE *fp = fopen(filename, "wb");

    // write header and information header
    fwrite(header, sizeof(unsigned char), BMP_HEADER_SIZE, fp);
    fwrite(info_header, sizeof(unsigned char), BMP_INFO_HEADER_SIZE, fp);

    // start writing pixels
    for (int i = 0; i < height; i++)
    {
        // write pixels
        fwrite(bmp + (width * 3 * i), sizeof(unsigned char), (width * 3), fp);

        // write padding
        fwrite(padding, sizeof(unsigned char), padding_size, fp);
    }

    // close file
    fclose(fp);
    return 0;
}

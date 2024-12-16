//
// Created by maxim on 17.11.24.
//

#ifndef BMP_H
#define BMP_H
#include <image.h>
#include <stdio.h>

#endif //BMP_H

enum READ_OP_STATUS {
    READ_OK = 0,
    INVALID_HEADER,
    IO_ERROR
};

enum WRITE_OP_STATUS {
    WRITE_OK = 0,
    HEADER_WRITING_ERROR,
    PIXELS_WRITING_ERROR
};


enum WRITE_OP_STATUS write_image(FILE *file, struct image *image);

enum READ_OP_STATUS read_bmp(FILE *file, struct image *image);

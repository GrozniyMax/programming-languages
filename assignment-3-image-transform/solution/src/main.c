#include <stdio.h>
#include <string.h>

#include <bmp.h>
#include <ccw90.h>
#include <cw90.h>
#include <fliph.h>
#include <flipv.h>
#include <image.h>
#include <io.h>
#include <none.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    // Проверяем количество аргументов
    if (argc != 4) {
        fprintf(stderr, "Usage: ./image-transform <source-image> <transformed-image> <tranformation>");
        return 1;
    }

    FILE *sourceFile;
    if (!open_file_read(argv[1], &sourceFile)) {
        fprintf(stderr, "Could not open source file: %s\n", argv[1]);
        return 2;
    }
    struct image sourceImage;
    if (read_bmp(sourceFile, &sourceImage) != READ_OK) {
        fprintf(stderr, "Could not read source image from %s\n", argv[1]);
        return 1;
    };

    if (!close_file(sourceFile)) {
        fprintf(stderr, "Could not close source file: %s\n", argv[1]);
    }

    struct image transformedImage;

    if (strcmp(argv[3], "ccw90") == 0 ) {
        transformedImage = transform_ccw90(&sourceImage);
    }
    else if (strcmp(argv[3], "cw90") == 0) {
        transformedImage = transform_cw90(&sourceImage);
    }
    else if (strcmp(argv[3], "flipv") == 0) {
        transformedImage = transform_flipv(&sourceImage);
    }
    else if (strcmp(argv[3], "fliph") == 0) {
        transformedImage = transform_fliph(&sourceImage);
    }
    else if (strcmp(argv[3], "none") == 0) {
        transformedImage = transform_none(&sourceImage);
    }else {
        fprintf(stderr, "Unknown transform type: %s\n", argv[3]);
        return 1;
    }

    FILE *destination;
    if (!open_file_write(argv[2], &destination)) {
        fprintf(stderr, "Could not open destination file: %s\n", argv[2]);
        return 1;
    }
    if (write_image(destination, &transformedImage) != WRITE_OK) {
        fprintf(stderr, "Could not write image to %s\n", argv[2]);
        return 1;
    }
    if (!close_file(destination)) {
        fprintf(stderr, "Could not close destination file: %s\n", argv[2]);
    }
    destroy_image(&sourceImage);
    destroy_image(&transformedImage);
    return 0;
}

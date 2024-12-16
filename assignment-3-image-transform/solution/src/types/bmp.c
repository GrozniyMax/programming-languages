#include <image.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


struct __attribute__((packed)) bmp_header {
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

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

uint64_t calculate_padding(struct image const *image) {
    return (4 - (image->width * sizeof(struct pixel)) % 4) % 4;
}

bool read_bmp_header(FILE *file, struct bmp_header *header) {
    return 1 == fread(header, sizeof(struct bmp_header), 1, file);
}

void handle_sigsegv(int sig) {
    fprintf(stderr, "Caught signal %d\n", sig);
    exit(12);
}

bool read_image(struct bmp_header *header, FILE *file, struct image *image) {
    signal(SIGSEGV, handle_sigsegv);
    *image = create_image(header->biWidth, header->biHeight);
    uint64_t padding = calculate_padding(image);
    for (uint32_t i = 0; i < header->biHeight; i++) {
        if (fread(image->data + i * image->width, sizeof(struct pixel), image->width, file) != image->width) {
            return false;
        };
        fseek(file, (long) padding, SEEK_CUR);
    }
    return true;
}

enum READ_OP_STATUS read_bmp(FILE *file, struct image *image) {
    struct bmp_header header = {0};
    bool io_status = true;
    io_status &= read_bmp_header(file, &header);
    if (header.bfType != 0x4D42 || header.biBitCount != 24) {
        return INVALID_HEADER;
    }
    io_status &= read_image(&header, file, image);
    return io_status ? READ_OK : IO_ERROR;
}


bool write_bmp_header(FILE *file, struct bmp_header *header) {
    size_t chunks = fwrite(header, sizeof(struct bmp_header), 1, file);
    return chunks == 1;
}

struct bmp_header create_bmp_header(struct image const *image) {
    struct bmp_header header = {
        .bfType = 0x4D42,
        .bfileSize = (uint32_t) (sizeof(struct bmp_header) + sizeof(struct pixel) * image->width * image->height),
        .bfReserved = 0,
        .bOffBits = sizeof(struct bmp_header),
        .biSize = 40,
        .biWidth = (uint32_t) image->width,
        .biHeight = (uint32_t) image->height,
        .biPlanes = 1,
        .biBitCount = 24,
        .biCompression = 0,
        .biSizeImage = (uint32_t) (image->width * image->height * sizeof(struct pixel)),
        .biXPelsPerMeter = 2835,
        .biYPelsPerMeter = 2835,
        .biClrUsed = 0,
        .biClrImportant = 0
    };
    return header;
}

bool write_image_data(FILE *file, struct image *img) {

    uint64_t padding = calculate_padding(img);
    uint8_t padding_data[3] = {0, 0, 0};
    for (uint64_t y = 0; y < img->height; y++) {
        if (fwrite(img->data + y * img->width, sizeof(struct pixel), img->width, file) != img->width) {
            return false;
        }
        fwrite(padding_data, 1, padding, file);
    }
    return true;
}


enum WRITE_OP_STATUS write_image(FILE *file, struct image *image) {
    struct bmp_header header = create_bmp_header(image);
    if (fwrite(&header, sizeof(struct bmp_header), 1, file) != 1) {
        return HEADER_WRITING_ERROR;
    }
    if (!write_image_data(file, image)) {
        return PIXELS_WRITING_ERROR;
    }
    return WRITE_OK;
}

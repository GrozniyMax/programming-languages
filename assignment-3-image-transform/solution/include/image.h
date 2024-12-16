
#ifndef IMAGE_H
#define IMAGE_H
#include <stdbool.h>
#include <stdint.h>
struct image {
    uint64_t width, height;
    struct pixel *data;
};
struct pixel {
    uint8_t b, g, r;
};

struct image create_image(uint64_t width, uint64_t height);

void destroy_image(struct image *image);

bool image_set(struct image const *image, uint64_t y, uint64_t x, struct pixel pixel);

struct pixel image_get(struct image const *image, uint64_t y, uint64_t x);

#endif //IMAGE_H





#include <image.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


struct image create_image(uint64_t width, uint64_t height) {
    struct image img;
    img.width = width;
    img.height = height;
    img.data = malloc(width * height * sizeof(struct pixel));
    if (img.data == NULL) {
        perror("Failed to allocate memory for image");
    }
    return img;
}

struct pixel image_get(struct image const *image, uint64_t y, uint64_t x) {
    return image->data[y*image->width + x];
}

bool image_set(struct image const *image, uint64_t y, uint64_t x, struct pixel pixel) {
    if (x>=image->width || y>=image->height) return false;
    image->data[y*image->width + x] = pixel;
    return true;
}

void destroy_image(struct image *image) {
    if (image->data != NULL) {
        free(image->data);
        image->data = NULL;
    }
}

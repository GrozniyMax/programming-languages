#include "image.h"
#include <stdint.h>

struct image transform_cw90(struct image const *image) {
    struct image new_image = create_image(image->height, image->width);

    uint64_t width = image->width;
    uint64_t height = image->height;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            image_set(&new_image, width - 1 - x, y, image_get(image, y,x));
        }
    }
    return new_image;
}

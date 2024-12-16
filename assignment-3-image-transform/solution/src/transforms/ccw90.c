#include "image.h"
#include <stdint.h>

struct image transform_ccw90(struct image const *image) {
    struct image new_image = create_image(image->height, image->width);

    uint64_t width = image->width;
    uint64_t height = image->height;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            image_set(&new_image, x, height - 1 - y, image_get(image, y, x));
        }
    }
    return new_image;
}

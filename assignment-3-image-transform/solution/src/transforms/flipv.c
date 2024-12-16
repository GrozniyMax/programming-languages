#include "image.h"
#include <stdint.h>

struct image transform_flipv(struct image const *image) {
    struct image new_img = create_image(image->width, image->height);

    uint64_t width = image->width;
    uint64_t height = image->height;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            image_set(&new_img, height-1-y, x, image_get(image, y, x));
        }
    }
    return new_img;
}

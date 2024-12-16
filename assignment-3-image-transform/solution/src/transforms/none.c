#include "image.h"
#include <string.h>

struct image transform_none(struct image const *img) {
    struct image new_img = create_image(img->width, img->height);
    memcpy(new_img.data, img->data, sizeof(struct pixel) * img->width * img->height);
    return new_img;
}

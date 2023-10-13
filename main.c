#include "image.h"
#include <stdio.h>

int main() {
    Image *rgb_img = load_from_ppm("a.ppm");

    if (rgb_img == NULL)
        return 1;

    int rows = get_rows(rgb_img), cols = get_cols(rgb_img);

    Image *gray_img = create(rows, cols, "P2");

    if (gray_img == NULL)
        return 1;

    rgb_to_gray(rgb_img, gray_img);
    write_to_ppm(gray_img, "b.ppm");
    free_image(rgb_img);
    free_image(gray_img);
    return 0;
}
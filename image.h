#ifndef IMAGE_H
#define IMAGE_H

typedef struct image Image;

// Define prototypes for the header

Image *create(int rows, int cols, char type[]);

Image *load_from_ppm(const char *filename);

int get_rows(Image *image);

int get_cols(Image *image);

void write_to_ppm(Image *image, const char *filename);

void rgb_to_gray(Image *image_rgb, Image *image_gray);

void free_image(Image *image);

#endif
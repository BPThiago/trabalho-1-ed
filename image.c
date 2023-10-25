#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct image {
    char type[3];
    int width;
    int height;
    unsigned char *matrix;
};

// Determine the expansion factor based on PPM image
// Returns 1 for "P2" (grayscale) and 3 for "P3" (color) images
static int get_expansion_factor(char type[]) {
    return strcmp(type, "P2") == 0 ? 1 : 3;
}

// Allocate memory for the pixel matrix of the image
static unsigned char *allocate_pixel_matrix(int width, int height, char type[]) {
    int exp_factor = get_expansion_factor(type);
    unsigned char *m = (unsigned char*)malloc(sizeof(unsigned char)*width*height*exp_factor);
    return m;
}

// Create a new image structure and initialize image properties
Image *create(int width, int height, char type[]) {
    Image *img = (Image *)malloc(sizeof(Image));
    if (img == NULL) {
        printf("Image can not be created.\n");
        return NULL;
    }
    strcpy(img->type, type);
    img->width = width;
    img->height = height;
    img->matrix = allocate_pixel_matrix(width, height, type);
    return img;
}

// Read image data from a PPM file
Image *load_from_ppm(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Image file can not be opened.\n");
        return NULL;
    }
    char type[3];
    int r, c, max_value, val;
    if (fscanf(f, "%s %u %u %u", type, &r, &c, &max_value) != 4) {
        printf("Invalid header");
        return NULL;
    }

    Image* img = create(r, c, type);
    for (int i=0; fscanf(f, "%u", &val) != EOF; i++)
        img->matrix[i] = val;
    
    fclose(f);
    return img;
}

int get_image_width(Image *image) {
    return image->width;
}

int get_image_height(Image *image) {
    return image->height;
}

// Write an image to a PPM file
void write_to_ppm(Image *image, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Image file cannot be created.\n");
        return;
    }
    fprintf(f, "%s\n%u %u\n%u\n", image->type, image->width, image->height, 255);
    for (int i=0; i < image->width; i++) {
        for (int j=0, mult = get_expansion_factor(image->type); j < mult*image->height; j++)
            fprintf(f, "%u ", image->matrix[i*image->height*mult + j]);
        fprintf(f, "\n");
    }
    fclose(f);
}

// Convert a color pixel RGB to grayscale
static int transform_to_gray(int r, int g, int b) {
    return 0.299*r + 0.587*g + 0.114*b;
}

// Convert an RGB image to a grayscale image
void rgb_to_gray(Image *image_rgb, Image *image_gray) {
    unsigned char *rgb_matrix = image_rgb->matrix, *gray_matrix = image_gray->matrix;
    for (int i=0, n=image_rgb->width*image_rgb->height; i < n; i++)
        gray_matrix[i] = transform_to_gray(rgb_matrix[i*3], rgb_matrix[i*3+1], rgb_matrix[i*3+2]);
}

// Free the memory associated with an image, including the pixel matrix
void free_image(Image *image) {
    free(image->matrix);
    free(image);
}
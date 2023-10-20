#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct image {
    char type[3];
    int rows;
    int cols;
    unsigned char *matrix;
};

static int get_expansion_factor(char type[]) {
    return strcmp(type, "P2") == 0 ? 1 : 3;
}

static unsigned char *allocate_pixel_matrix(int rows, int cols, char type[]) {
    int mult = get_expansion_factor(type);
    unsigned char *m = malloc(sizeof(unsigned char)*rows*cols*mult);
    return m;
}

Image *create(int rows, int cols, char type[]) {
    Image *img = malloc(sizeof(Image));
    strcpy(img->type, type);
    img->rows = rows;
    img->cols = cols;
    img->matrix = allocate_pixel_matrix(rows, cols, type);
    return img;
}

Image *load_from_ppm(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Image file can not be opened.");
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

int get_rows(Image *image) {
    return image->rows;
}

int get_cols(Image *image) {
    return image->cols;
}

void write_to_ppm(Image *image, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Image file cannot be created.");
        return;
    }
    fprintf(f, "%s\n%u %u\n%u\n", image->type, image->rows, image->cols, 255);  // TODO: É necessário mudar a assinatura
    for (int i=0; i < image->rows; i++) {
        for (int j=0, mult = get_expansion_factor(image->type); j < mult*image->cols; j++)
            fprintf(f, "%u ", image->matrix[i*image->cols*mult + j]);
        fprintf(f, "\n");
    }
    fclose(f);
}

static int transform_to_gray(int r, int g, int b) {
    return 0.299*r + 0.587*g + 0.114*b;
}

void rgb_to_gray(Image *image_rgb, Image *image_gray) {
    unsigned char *rgb_matrix = image_rgb->matrix, *gray_matrix = image_gray->matrix;
    for (int i=0, n=image_rgb->rows*image_rgb->cols; i < n; i++)
        gray_matrix[i] = transform_to_gray(rgb_matrix[i*3], rgb_matrix[i*3+1], rgb_matrix[i*3+2]);
}

void free_image(Image *image) {
    free(image->matrix);
    free(image);
}
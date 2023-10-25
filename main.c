#include "image.h"
#include <stdio.h>
#include <string.h>

int main() {
    char path[101];
    int op;
    printf("Qual opcao voce deseja (0: Caminho padrao; 1: Inserir um caminho)? ");
    scanf("%d", &op);
    if (op == 0)
        strcpy(path, "images/color/lena.ppm");
    else {
        printf("Insira o caminho: ");
        scanf("%s", path);
    }
    Image *rgb_img = load_from_ppm(path);

    if (rgb_img == NULL)
        return 1;

    int rows = get_image_width(rgb_img), cols = get_image_height(rgb_img);

    Image *gray_img = create(rows, cols, "P2");

    if (gray_img == NULL)
        return 1;

    rgb_to_gray(rgb_img, gray_img);
    write_to_ppm(gray_img, "images/grayscale/convertido.ppm");
    free_image(rgb_img);
    free_image(gray_img);
    return 0;
}
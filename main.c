#include "image.h"
#include <stdio.h>
#include <string.h>

int main() {
    char path[101];
    int option;
    
    printf("Qual opcao voce deseja (0: Caminho padrao; 1: Inserir um caminho)? ");
    scanf("%d", &option);
    if (option == 0)
        strcpy(path, "images/color/lena.ppm");
    else {
        printf("Insira o caminho: ");
        scanf("%s", path);
    }
    Image *rgb_img = load_from_ppm(path);

    if (rgb_img == NULL) {
        printf("Image file can not be opened.\n");
        return 1;
    }

    int img_width = get_image_width(rgb_img), img_height = get_image_height(rgb_img);

    Image *gray_img = create(img_width, img_height, "P2");

    if (gray_img == NULL) {
        printf("Image can not be created.\n");
        return 1;
    }

    rgb_to_gray(rgb_img, gray_img);
    write_to_ppm(gray_img, "images/grayscale/convertido.ppm");
    
    free_image(rgb_img);
    free_image(gray_img);
    return 0;
}
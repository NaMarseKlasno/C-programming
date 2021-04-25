#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "transformations.h"
#include <math.h>

int main()
{
    FILE * file = fopen("assets/lenna.bmp", "rb");
    if (file == NULL) return 1;

    FILE * output = fopen("assets/output.bmp", "wb");
    if (output == NULL) {
        fclose(file);
        return 1;
    }
    //printf("%f\n", round(0.86));

    /*
    struct bmp_header* header = calloc(1, sizeof(struct bmp_header));
    if (header == NULL) return 1;
    header = read_bmp_header(file);

    struct pixel* pixels = calloc(header->height*header->width, sizeof(struct pixel));
    if (pixels == NULL) return 1;
    pixels = read_data(file, header);


    for (int i = 0; i < header->width*header->height ; ++i) {
        printf("R:%d G:%d B:%d\n", pixels[i].red, pixels[i].green, pixels[i].blue);
    }
    */

    // ******  Allocate data for full image
    uint32_t x = 0, y = 0, h = 10, w = 12;
    float n = 1.5;

    struct bmp_image* image = read_bmp(file);

    struct bmp_image* image_r = crop(NULL, y, x, h, w);
    struct bmp_image* image2 = rotate_right(image);
    struct bmp_image* image3 = rotate_left(image);
    struct bmp_image* image4 = flip_vertically(image);
    struct bmp_image* image5 = flip_horizontally(image);
    struct bmp_image* image6 = scale(image, n);

    write_bmp(output, image2);

    free_bmp_image(image);
    free_bmp_image(image2);
    free_bmp_image(image3);
    free_bmp_image(image4);
    free_bmp_image(image5);
    free_bmp_image(image6);
    free_bmp_image(image_r);

    fclose(file);
    fclose(output);

    return 0;
}

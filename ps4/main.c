#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "transformations.h"

int main()
{
    FILE * file = fopen("assets/cj.bmp", "rb");
    if (file == NULL) return 1;

    FILE * output = fopen("assets/output.bmp", "wb");
    if (output == NULL) {
        fclose(file);
        return 1;
    }


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

    struct bmp_image* image = NULL;
    struct bmp_image* image_r = NULL;

    image = read_bmp(file);

    uint32_t x = 0, y = 0, h = 10, w = 11;
    image_r = crop(image, y, x, h, w);
    if (image_r == NULL) printf("returned NULL!\n");

    write_bmp(output, image_r);

    image_r = rotate_right(image);
    image_r = rotate_left(image);
    image_r = flip_vertically(image);
    image_r = flip_horizontally(image);

    fclose(file);
    fclose(output);
    //free(image_r);
    //free(image);

    return 0;
}

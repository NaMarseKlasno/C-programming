#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "transformations.h"
#include <math.h>

int main()
{
    // (bpp * width) % 4 == 0?0 : 4 - (bpp*width)%4;

    FILE * file = fopen("assets/lenna.bmp", "rb");
    if (file == NULL) return 1;

    FILE * output = fopen("assets/output.bmp", "wb");
    if (output == NULL) {
        fclose(file);
        return 1;
    }

    // ******  Allocate data for full image
    uint32_t y = 0, x = 0, h = 160, w = 256;
    float n = 2.761034;

    struct bmp_image* image = read_bmp(file);
    struct bmp_image* image_r = crop(image, y, x, h, w);
    struct bmp_image* image2 = rotate_right(image);
    struct bmp_image* image3 = rotate_left(image);
    struct bmp_image* image4 = flip_vertically(image);
    struct bmp_image* image5 = flip_horizontally(image);
    struct bmp_image* image6 = scale(image, n);
    struct bmp_image* image7 = extract(image, "r");

    //printf("%d\n", image_r->header->image_size);
    //printf("%d %d %d\n", image_r->data->red, image_r->data->green, image_r->data->blue);
    write_bmp(output, image_r);


    free_bmp_image(image);
    free_bmp_image(image2);
    free_bmp_image(image3);
    free_bmp_image(image4);
    free_bmp_image(image5);
    free_bmp_image(image6);
    free_bmp_image(image7);
    free_bmp_image(image_r);

    fclose(file);
    fclose(output);

    return 0;
}

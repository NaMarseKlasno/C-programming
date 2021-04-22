#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main()
{
    FILE * file = fopen("assets/zakat.bmp", "rb");
    if (file == NULL) {
        printf("ERROR\n");
        return 1;
    }

    /**
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

    struct bmp_image* image = calloc(1, sizeof(struct bmp_image));
    if (image == NULL) return 1;

    image = read_bmp(file);

    FILE * output = fopen("output.bmp", "wb");
    printf("result: %d\n", write_bmp(output, image));

    fclose(file);
    fclose(output);
    //free(pixels);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main()
{
    FILE * file = fopen("assets/cj.bmp", "rb");
    if (file == NULL) {
        printf("ERROR\n");
        return 1;
    }
    struct bmp_header *header = calloc(1, sizeof(struct bmp_header));
    header = read_bmp_header(file);

    struct pixel* pixels = calloc(header->height*header->width, sizeof(struct pixel));
    pixels = read_data(file, header);

    for (int i = 0; i < header->width*header->height ; ++i) {
        printf("R:%d G:%d B:%d\n", pixels[i].red, pixels[i].green, pixels[i].blue);
    }


    fclose(file);
    free(pixels);
    return 0;
}

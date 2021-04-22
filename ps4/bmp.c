#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>


struct bmp_header* read_bmp_header (FILE* stream) {
    if (stream == NULL) return NULL;
    struct bmp_header *header = calloc(1, sizeof(struct bmp_header));

    fread(header, 54, 1, stream);

    char * pUint16 = (char*)&header->type;
    if (pUint16[0] != 'B' && pUint16[1] != 'M') {
        free(header);
        return NULL;
    }

    /**
    printf("First chars: %c%c\n", pUint16[0], pUint16[1]);
    printf("Size: %d\n", header->size);
    printf("Num of colors: %d\n", header->num_colors);
    printf("Image size: %d\n", header->image_size);
    printf("X_ppm: %d\n", header->x_ppm);
    printf("Y_ppm: %d\n", header->y_ppm);
    */

    return header;
}


struct pixel* read_data (FILE* stream, const struct bmp_header* header) {
    if (stream == NULL || header == NULL) return NULL;

    struct pixel* imagePixels = calloc(header->height * header->width, sizeof(struct pixel));

    uint32_t row = 0;

    fseek(stream, sizeof(struct bmp_header), 0);
    while (row < header->height)
    {
        for (uint32_t j = 0; j < header->width; j++) fread(&imagePixels[(row * header->width) + j], sizeof(struct pixel), 1, stream);
        fseek(stream, (header->width)%4, SEEK_CUR);

        ++row;
    } return imagePixels;
}


struct bmp_image* read_bmp (FILE* stream) {
    if (stream == NULL) {
        printf("Error: This is not a BMP file.\n");
        return NULL;
    }

    struct bmp_image* image = calloc(1, sizeof(struct bmp_image));
    if (image == NULL) return NULL;

    image->header = read_bmp_header(stream);
    if (image->header == NULL) {
        printf("Error: Corrupted BMP file.\n");
        return NULL;
    }
    image->data = read_data(stream, image->header);
    if (image->data == NULL) {
        printf("Error: Corrupted BMP file.\n");
        return NULL;
    }

    return image;
}

bool write_bmp (FILE* stream, const struct bmp_image* image) {
    if (stream == NULL || image == NULL || image->data == NULL) return false;

    fwrite(image->header, sizeof(struct bmp_header), 1, stream);

    uint32_t row = 0;

    while (row < image->header->height)
    {
        for (uint32_t j = 0; j < image->header->width; j++)
            fwrite(&image->data[(row * image->header->width) + j], sizeof(struct pixel), 1, stream);
        ++row;
    }

    return true;
}

void free_bmp_image (struct bmp_image* image) {
    if (image == NULL) return;
    if(image->header!=NULL) free(image->header);

    if(image->data!=NULL) free(image->data);
    free(image);
}
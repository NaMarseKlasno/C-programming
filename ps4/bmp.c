#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>


struct bmp_header* read_bmp_header (FILE* stream) {
    if (stream == NULL) return NULL;

    fseek(stream, 0, SEEK_END);
    long file_len = ftell(stream);
    if(file_len <= 0) {
        return NULL;
    }
    fseek(stream, 0, SEEK_SET);
    char *stream_as_string = (char *)malloc(file_len * sizeof(char));
    fread(stream_as_string, file_len, 1, stream);
    int i = 0;
    bool file_bmp = false;
    do{
        if(stream_as_string[i] == 66 && stream_as_string[i + 1] == 77){
            file_bmp = true;
            fseek(stream, i, SEEK_SET);
            break;
        }
        i += 1;
    }while(i < file_len);
    free(stream_as_string);
    if(file_bmp == false){
        return NULL;
    }


    struct bmp_header *header = calloc(1, sizeof(struct bmp_header));
    if (header == NULL) return NULL;

    if (fread(header, sizeof(struct bmp_header), 1, stream) != 1) {
        free(header);
        return NULL;
    }
    char * pUint16 = (char*)&header->type;
    if ((header -> type != 0x4d42) || (pUint16[0] != 'B') || (pUint16[1] != 'M')) {
        free(header);
        return NULL;
    } if (header->height <= 0) {
        free(header);
        return NULL;
    } if (header->width <= 0) {
        free(header);
        return NULL;
    } uint32_t bpp = header->bpp / 8, pad = 0;
    if ((bpp * header->width) % 4 != 0) pad = 4 - (bpp * header->width) % 4;

    header->image_size = ((header->width * bpp) + pad) * header->height;
    header->size = header->image_size + header->offset;

    if (header->offset != 54) {
        free(header);
        return NULL;
    } if (header->dib_size != 40) {
        free(header);
        return NULL;
    } if (header->bpp != 24) {
        free(header);
        return NULL;
    } if (header->compression != 0) {
        free(header);
        return NULL;
    }

    /*
    uint32_t bpp = header->bpp / (uint32_t)8, pr = 4 - (bpp * header->width) % 4;
    if ((bpp * header->width) % 4 == 0) pr = 0;

    uint32_t im_size = ((header->width * bpp) + pr) * header->height;

    if (header->image_size != im_size || header->size != (im_size + header->offset)){
        free(header);
        return NULL;
    }
    */

    return header;
}


struct pixel* read_data (FILE* stream, const struct bmp_header* header) {
    if (stream == NULL || header == NULL) return NULL;

    struct pixel* imagePixels = calloc(header->height * header->width, sizeof(struct pixel));
    if (imagePixels == NULL) return NULL;

    uint32_t row = 0;

    fseek(stream, sizeof(struct bmp_header), 0);
    while (row < header->height)
    {
        for (uint32_t j = 0; j < header->width; j++)
            fread(&imagePixels[(row * header->width) + j], sizeof(struct pixel), 1, stream);
        fseek(stream, (header->width)%4, SEEK_CUR);
        ++row;
    } return imagePixels;
}


struct bmp_image* read_bmp (FILE* stream) {
    if (stream == NULL) return NULL;

    struct bmp_image* image = calloc(1, sizeof(struct bmp_image));
    if (image == NULL) return NULL;

    image->header = read_bmp_header(stream);
    if (image->header == NULL) {
        printf("Error: This is not a BMP file.\n");
        free_bmp_image(image);
        return NULL;
    }
    image->data = read_data(stream, image->header);
    if (image->data == NULL) {
        printf("Error: Corrupted BMP file.\n");
        free_bmp_image(image);
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
    if (image->header != NULL) free(image->header);
    if (image->data != NULL) free(image->data);
    free(image);
}

// Qk1OAAAAAAAAADYAAAAoAAAABAAAAAIAAAABABgAAAAAABgAAAAjLgAAIy4AAAAAAAAAAAAAAAAAAP8A/wAA/////wAAAAD/AP8AAAAA
//echo "Qk1OAAAAAAAAADYAAAAoAAAAAwAAAAIAAAABABgAAAAAABgAAAAjLgAAIy4AAAAAAAAAAAAA/////wAAAAAAAAAA/wD/AP8A/wD/AAAA" | base64 -d > j1.bmp

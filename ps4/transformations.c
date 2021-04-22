#include "bmp.h"
#include <stdlib.h>


struct pixel** one_to_two (const struct pixel* data, const struct bmp_header* header);
struct pixel* two_to_one (struct pixel **image, const uint32_t height, const uint32_t width);


struct bmp_image* flip_horizontally (const struct bmp_image* image)
{
    // ****** null check
    if (image == NULL || image->data == NULL) return NULL;

    // ****** memory allocation for a new picture
    struct bmp_image* rotated_image = calloc(1, sizeof(struct bmp_image));
    if (rotated_image == NULL) return NULL;
    rotated_image->header = image->header;
    struct pixel **arr = calloc(image->header->height, sizeof(struct pixel**));
    struct pixel **niga = calloc(image->header->height, sizeof(struct pixel**));
    if (arr == NULL || niga == NULL) return NULL;
    for (uint32_t i = 0; i < image->header->height; ++i) {
        arr[i] = calloc(image->header->width, sizeof(struct pixel*));
        niga[i] = calloc(image->header->width, sizeof(struct pixel*));
        if (arr[i] == NULL || niga[i] == NULL) return NULL;
    }

    arr = one_to_two(image->data, image->header);
    // ****** copy arr to niga
    for (uint32_t i = 0; i < image->header->height; ++i)
        for (uint32_t j = 0; j < image->header->width; ++j)
            niga[i][j] = arr[i][j];

    // ****** transform image there
    for (uint32_t i = 0; i < image->header->height; ++i)
        for (uint32_t j = 0, jx = image->header->width-1; j < image->header->width; ++j, --jx)
            arr[i][j] = niga[i][jx];

    rotated_image->data = two_to_one(arr, image->header->height, image->header->width);

    for (uint32_t i = 0; i < image->header->height; ++i) {
        free(arr[i]);
        free(niga[i]);
    }
    free(arr);
    free(niga);

    return rotated_image;
}


struct bmp_image* flip_vertically (const struct bmp_image* image)
{
    // ****** null check
    if (image == NULL || image->data == NULL) return NULL;

    // ****** memory allocation for a new picture
    struct bmp_image* rotated_image = calloc(1, sizeof(struct bmp_image));
    if (rotated_image == NULL) return NULL;
    rotated_image->header = image->header;
    struct pixel **arr = calloc(image->header->height, sizeof(struct pixel**));
    struct pixel **niga = calloc(image->header->height, sizeof(struct pixel**));
    if (arr == NULL || niga == NULL) return NULL;
    for (uint32_t i = 0; i < image->header->height; ++i) {
        arr[i] = calloc(image->header->width, sizeof(struct pixel*));
        niga[i] = calloc(image->header->width, sizeof(struct pixel*));
        if (arr[i] == NULL || niga[i] == NULL) return NULL;
    }

    arr = one_to_two(image->data, image->header);
    // ****** copy arr to niga
    for (uint32_t i = 0; i < image->header->height; ++i)
        for (uint32_t j = 0; j < image->header->width; ++j)
            niga[i][j] = arr[i][j];

    // ****** transform image there
    for (uint32_t i = 0, ix = image->header->height-1; i < image->header->height; ++i, --ix)
        for (uint32_t j = 0; j < image->header->width; ++j, --jx)
            arr[i][j] = niga[ix][j];

    rotated_image->data = two_to_one(arr, image->header->height, image->header->width);

    for (uint32_t i = 0; i < image->header->height; ++i) {
        free(arr[i]);
        free(niga[i]);
    }
    free(arr);
    free(niga);

    return rotated_image;
}

struct pixel** one_to_two (const struct pixel* data, const struct bmp_header* header) {
    // ****** null check
    if (data == NULL || header == NULL) return NULL;

    // ****** memory allocation
    struct pixel** image = calloc(header->height, sizeof(struct pixel**));
    if (image == NULL) return NULL;

    for (uint32_t i = 0; i < header->height; ++i) {
        image[i] = calloc(header->width, sizeof(struct pixel*));
        if (image[i] == NULL) return NULL;
    }

    for (uint32_t row = 0; row < header->height; ++row)
        for (uint32_t column = 0; column < header->width; column++)
            image[row][column] = data[(row * header->width) + column];

    return image;
}

struct pixel* two_to_one (struct pixel **image, const uint32_t height, const uint32_t width) {
    if (image == NULL) return NULL;

    struct pixel* imagePixels = calloc(height * width, sizeof(struct pixel*));

    for (uint32_t row = 0; row < height; ++row)
        for (uint32_t column = 0; column < width; column++)
            imagePixels[(row * width) + column] = image[row][column];

    return imagePixels;
}


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
    for (uint32_t i = 0; i < image->header->height; ++i) {
        free(arr[i]);
        free(niga[i]);
    } free(arr);
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
    if (arr == NULL) {
        free(arr);
        return NULL;
    }
    struct pixel **niga = calloc(image->header->height, sizeof(struct pixel**));
    if (niga == NULL) {
        free(niga);
        free(arr);
        return NULL;
    }
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
        for (uint32_t j = 0; j < image->header->width; ++j)
            arr[i][j] = niga[ix][j];

    rotated_image->data = two_to_one(arr, image->header->height, image->header->width);

    for (uint32_t i = 0; i < image->header->height; ++i) {
        free(arr[i]);
        free(niga[i]);
    } free(arr);
    free(niga);

    return rotated_image;
}


struct bmp_image* rotate_right(const struct bmp_image* image) {
    // ****** null check
    if (image == NULL || image->data == NULL) return NULL;

    // ****** memory allocation for a new picture
    struct bmp_image* rotated_image = calloc(1, sizeof(struct bmp_image));
    if (rotated_image == NULL) {
        free(rotated_image);
        return NULL;
    }

    //printf("h:%d, w:%d\n", image->header->height, image->header->width);
    rotated_image->header = image->header;
    rotated_image->header->width = image->header->height;
    rotated_image->header->height = image->header->width;

    //printf("h:%d, w:%d\n", rotated_image->header->height, rotated_image->header->width);

    struct pixel **arr = calloc(image->header->height, sizeof(struct pixel**));
    if (arr == NULL) {
        free(arr);
        return NULL;
    }
    struct pixel **niga = calloc(image->header->width, sizeof(struct pixel**));
    if (niga == NULL) {
        free(arr);
        free(niga);
        return NULL;
    }
    for (uint32_t i = 0; i < image->header->height; ++i) {
        arr[i] = calloc(image->header->width, sizeof(struct pixel*));
        niga[i] = calloc(image->header->height, sizeof(struct pixel*));
        if (arr[i] == NULL || niga[i] == NULL) return NULL;
    }

    arr = one_to_two(image->data, image->header);
    // ****** copy arr to niga
    for (uint32_t i = 0; i < image->header->width; ++i)
        for (uint32_t j = 0; j < image->header->height; ++j)
            niga[i][j] = arr[i][j];

    // ****** transform image there
    //for (uint32_t i = 0; i < image->header->height; ++i)
    //    for (uint32_t j = 0, jx = image->header->width-1; j < image->header->width; ++j, --jx)
    //        arr[i][j] = niga[i][jx];

    rotated_image->data = two_to_one(niga, image->header->height, image->header->width);

    for (uint32_t i = 0; i < image->header->height; ++i) {
        free(arr[i]);
        free(niga[i]);
    }

    for (uint32_t i = 0; i < image->header->height; ++i) {
        free(arr[i]);
    } free(arr);
    for (uint32_t i = 0; i < image->header->width; ++i) {
        free(niga[i]);
    } free(niga);

    return rotated_image;
}

struct bmp_image* rotate_left(const struct bmp_image* image) {
    return NULL;
}



struct pixel** one_to_two (const struct pixel* data, const struct bmp_header* header) {
    // ****** null check
    if (data == NULL || header == NULL) return NULL;

    // ****** memory allocation
    struct pixel** image = calloc(header->height, sizeof(struct pixel**));
    if (image == NULL) {
        free(image);
        return NULL;
    }

    for (uint32_t i = 0; i < header->height; ++i) {
        image[i] = calloc(header->width, sizeof(struct pixel*));
        if (image[i] == NULL) {
            return NULL;
        }
    }

    for (uint32_t row = 0; row < header->height; ++row)
        for (uint32_t column = 0; column < header->width; column++)
            image[row][column] = data[(row * header->width) + column];

    return image;
}

struct pixel* two_to_one (struct pixel **image, const uint32_t height, const uint32_t width) {
    if (image == NULL) return NULL;

    struct pixel* imagePixels = calloc(height * width, sizeof(struct pixel*));
    if (imagePixels == NULL) {
        free(imagePixels);
        return NULL;
    }

    for (uint32_t row = 0; row < height; ++row)
        for (uint32_t column = 0; column < width; column++)
            imagePixels[(row * width) + column] = image[row][column];

    return imagePixels;
}


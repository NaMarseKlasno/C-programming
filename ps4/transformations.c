#include "bmp.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>


struct bmp_header* copyHeader(struct bmp_header* toCopy);
struct pixel* copyData(struct pixel* toCopy, long countPixels);
bool chekIn(const char str[], char ch);



struct bmp_image* flip_horizontally (const struct bmp_image* image)
{
    if (image == NULL || image->data == NULL || image->header == NULL) {
        return NULL;
    }

    struct bmp_image* res = malloc(sizeof(struct bmp_image));

    res->header = copyHeader(image->header);
    res->data = copyData(image->data,image->header->height * image->header->width);

    for (int i = 0; i < image->header->height; ++i)
        for (int j = 0; j < image->header->width; ++j)
            res->data[i * res->header->width + j] = image->data[i * image->header->width + image->header->width - j-1];

    return res;
}


struct bmp_image* flip_vertically(const struct bmp_image* image)
{
    if (image == NULL || image->data == NULL || image->header == NULL) {
        return NULL;
    }

    struct bmp_image* res = malloc(sizeof(struct bmp_image));

    res->header = copyHeader(image->header);
    res->data = copyData(image->data,image->header->height * image->header->width);

    for (int i = 0; i < image->header->height; ++i)
        for (int j = 0; j < image->header->width; ++j)
            res->data[i * res->header->width + j] = image->data[(image->header->height-1-i) * image->header->width+j];

    return res;
}


struct bmp_image* rotate_right(const struct bmp_image* image)
{
    if (image == NULL || image->data == NULL || image->header == NULL) {
        return NULL;
    }

    struct bmp_image* res = malloc(sizeof(struct bmp_image));

    res->header = copyHeader(image->header);
    res->header->width = image->header->height;
    res->header->height = image->header->width;
    (((image->header->bpp/8)*res->header->width) % 4 != 0) ? (res->header->image_size = ((4 - ((image->header->bpp/8)*res->header->width)%4) + res->header->width*(image->header->bpp/8))*res->header->height) : (res->header->image_size = res->header->width * (image->header->bpp/8) * res->header->height);
    res->header->size = res->header->image_size+res->header->offset;

    res->data = calloc(image->header->height * image->header->width, sizeof(struct pixel));


    for (int i = 0; i < image->header->width; ++i)
        for (int j = 0; j < image->header->height; ++j)
            res->data[(i*image->header->height)+j] = image->data[(j*image->header->width)+image->header->width-i-1];

    return res;
}


struct bmp_image* rotate_left(const struct bmp_image* image)
{
    if (image == NULL || image->data == NULL || image->header == NULL) {
        return NULL;
    }

    struct bmp_image* res = malloc(sizeof(struct bmp_image));
    if (res == NULL) return NULL;

    res->header = copyHeader(image->header);
    res->header->width = image->header->height;
    res->header->height = image->header->width;
    (((image->header->bpp/8)*res->header->width) % 4 != 0) ? (res->header->image_size = ((4 - ((image->header->bpp/8)*res->header->width)%4) + res->header->width*(image->header->bpp/8))*res->header->height) : (res->header->image_size = res->header->width * (image->header->bpp/8) * res->header->height);
    res->header->size = res->header->image_size+res->header->offset;

    res->data = calloc(image->header->height * image->header->width, sizeof(struct pixel));

    for (int i = 0; i < image->header->width; ++i)
        for (int j = 0; j < image->header->height; ++j)
            res->data[(i*image->header->height)+image->header->height-j-1] = image->data[(j*image->header->width)+i];

    return res;
}


struct bmp_image* scale(const struct bmp_image* image, float factor)
{
    if (image == NULL || image->data == NULL || image->header == NULL || factor <= 0) {
        return NULL;
    }

    struct bmp_image* res = malloc(sizeof(struct bmp_image));

    res->header = copyHeader(image->header);

    res->header->width = round(image->header->width * factor);
    res->header->height = round(image->header->height * factor);
    (((image->header->bpp/8) * res->header->width) % 4 != 0) ? (res->header->image_size = ((4 - ((image->header->bpp/8) * res->header->width) % 4) + res->header->width * (image->header->bpp/8)) * res->header->height) : (res->header->image_size = res->header->width * (image->header->bpp/8) * res->header->height);
    res->header->size = res->header->image_size + res->header->offset;

    res->data = calloc(res->header->height * res->header->width, sizeof(struct pixel));

    for (int i = 0, k = 0; i < res->header->height; ++i)
        for (int j = 0; j < res->header->width; ++j, ++k)
            res->data[k] = image->data[( ((int)(i*image->header->height)/res->header->height)*image->header->width)+((int)(j*image->header->width)/res->header->width)];

    return res;
}


struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width)
{
    if (image==NULL || image->data==NULL || image->header==NULL || start_y<0 || start_y>image->header->height || height<=0 || start_y+height>image->header->height) return NULL;
    if (start_x+width>image->header->width || start_y+height>image->header->height || width<=0 || start_x<0 || start_x>image->header->width) return NULL;

    struct bmp_image* res = malloc(sizeof(struct bmp_image));

    res->header = copyHeader(image->header);
    res->header->width = width;
    res->header->height = height;

    uint32_t pr;
    (((image->header->bpp/8) * width) % 4 != 0) ? (pr = 4 - ((image->header->bpp/8) * width) % 4) : (pr = 0);
    res->header->image_size = (((width*image->header->bpp/8) + pr) * height);
    res->header->size = res->header->image_size + res->header->offset;

    res->data = calloc(res->header->height * res->header->width, sizeof(struct pixel));

    for (int i = 0; i < res->header->height; ++i)
        for (int j = 0; j < res->header->width; ++j)
            res->data[(i*res->header->width)+j] = image->data[(i*image->header->width)+j];

    return res;
}


struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep)
{
    if (image == NULL || colors_to_keep == NULL || image->data == NULL || image->header == NULL) return NULL;

    for (int i = 0; i < strlen(colors_to_keep); ++i) if (colors_to_keep[i] != 'r' && colors_to_keep[i] != 'g' && colors_to_keep[i] != 'b') return NULL;
    if (strlen(colors_to_keep) > 3) return NULL;

    struct bmp_image* res = malloc(sizeof(struct bmp_image));

    res->header = copyHeader(image->header);
    res->data = copyData(image->data,image->header->height * image->header->width);

    for (int i = 0; i < image->header->height; ++i)
    {
        for (int j = 0; j < image->header->width; ++j)
        {
            (chekIn(colors_to_keep, 'r')) ? (res->data[(j * image->header->height) + i].red = image->data[(j * image->header->height) + i].red)     : (res->data[(j * image->header->height) + i].red = 0);
            (chekIn(colors_to_keep, 'g')) ? (res->data[(j * image->header->height) + i].green = image->data[(j * image->header->height) + i].green) : (res->data[(j * image->header->height) + i].green = 0);
            (chekIn(colors_to_keep, 'b')) ? (res->data[(j * image->header->height) + i].blue = image->data[(j * image->header->height) + i].blue)   : (res->data[(j * image->header->height) + i].blue = 0);
        }
    }

    return res;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////



struct bmp_header* copyHeader(struct bmp_header* toCopy)
{
    struct bmp_header* header = malloc(sizeof(struct bmp_header));

    header->type = toCopy->type;
    header->size = toCopy->size;
    header->reserved1= toCopy->reserved1;
    header->reserved2 = toCopy->reserved2;
    header->offset = toCopy->offset;
    header->dib_size = toCopy->dib_size;
    header->width = toCopy->width;
    header->height= toCopy->height;
    header->planes = toCopy->planes;
    header->bpp= toCopy->bpp;
    header->compression = toCopy->compression;
    header->image_size = toCopy->image_size;
    header->x_ppm= toCopy->x_ppm;
    header->y_ppm = toCopy->y_ppm;
    header->num_colors = toCopy->num_colors;
    header->important_colors = toCopy->important_colors;

    return header;
}

struct pixel* copyData(struct pixel* toCopy, long countPixels)
{
    struct pixel* data = malloc(countPixels * sizeof(struct pixel));

    for (int i = 0; i < countPixels; ++i)
    {
        data[i].red   = toCopy[i].red;
        data[i].green = toCopy[i].green;
        data[i].blue  = toCopy[i].blue;
    }

    return data;
}

bool chekIn(const char str[], char ch)
{
    for (int i = 0; i < strlen(str); ++i) if (str[i] == ch) return true;
    return false;
}

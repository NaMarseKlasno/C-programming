#include "bmp.h"
#include <stdlib.h>
#include <math.h>


struct pixel** one_to_two (const struct pixel* data, const struct bmp_header* header);
struct pixel* two_to_one (struct pixel **image, const uint32_t height, const uint32_t width);
void free_arrays (struct pixel ** array, const uint32_t h);

struct bmp_image* flip_horizontally (const struct bmp_image* image)
{
    // ****** null check
    if (image == NULL || image->data == NULL || image->header == NULL) return NULL;

    // ****** memory allocation for a new picture
    struct bmp_image* rotated_image = calloc(1, sizeof(struct bmp_image));
    if (rotated_image == NULL) return NULL;

    rotated_image->header = calloc(1, sizeof(struct bmp_header));
    rotated_image->header->type = image->header->type;
    rotated_image->header->size = image->header->size;
    rotated_image->header->reserved1= image->header->reserved1;
    rotated_image->header->reserved2 = image->header->reserved2;
    rotated_image->header->offset = image->header->offset;
    rotated_image->header->dib_size = image->header->dib_size;
    rotated_image->header->width = image->header->width;
    rotated_image->header->height= image->header->height;
    rotated_image->header->planes = image->header->planes;
    rotated_image->header->bpp= image->header->bpp;
    rotated_image->header->compression = image->header->compression;
    rotated_image->header->image_size = image->header->image_size;
    rotated_image->header->x_ppm= image->header->x_ppm;
    rotated_image->header->y_ppm = image->header->y_ppm;
    rotated_image->header->num_colors = image->header->num_colors;
    rotated_image->header->important_colors = image->header->important_colors;

    //rotated_image->header = image->header;
    //struct pixel **arr = calloc(image->header->height, sizeof(struct pixel**));
    //if (arr == NULL) {
    //    free_bmp_image(rotated_image);
    //    return NULL;
    //}
    struct pixel **niga = calloc(image->header->height, sizeof(struct pixel**));
    if (niga == NULL) {
        //free(arr);
        free_bmp_image(rotated_image);
        return NULL;
    }

    for (uint32_t i = 0; i < image->header->height; ++i) {
        //arr[i] = calloc(image->header->width, sizeof(struct pixel*));
        niga[i] = calloc(image->header->width, sizeof(struct pixel*));
        if (niga[i] == NULL) {
            //free_arrays(arr, image->header->height);
            free_arrays(niga, image->header->height);
            free_bmp_image(rotated_image);
            return NULL;
        }
    }

    struct pixel **arr = one_to_two(image->data, image->header);
    if (arr == NULL) {
        free_arrays(arr, image->header->height);
        free_arrays(niga, image->header->height);
        free_bmp_image(rotated_image);
        return NULL;
    }
    // ****** copy arr to niga
    for (uint32_t i = 0; i < image->header->height; ++i)
        for (uint32_t j = 0; j < image->header->width; ++j)
            niga[i][j] = arr[i][j];

    // ****** transform image there
    for (uint32_t i = 0; i < image->header->height; ++i)
        for (uint32_t j = 0, jx = image->header->width-1; j < image->header->width; ++j, --jx)
            arr[i][j] = niga[i][jx];

    rotated_image->data = two_to_one(arr, image->header->height, image->header->width);

    free_arrays(arr, image->header->height);
    free_arrays(niga, image->header->height);
    return rotated_image;
}


struct bmp_image* flip_vertically (const struct bmp_image* image)
{
    // ****** null check
    if (image == NULL || image->data == NULL) return NULL;

    // ****** memory allocation for a new picture
    struct bmp_image* rotated_image = calloc(1, sizeof(struct bmp_image));
    if (rotated_image == NULL) return NULL;

    rotated_image->header = malloc(sizeof(struct bmp_header));
    rotated_image->header->type = image->header->type;
    rotated_image->header->size = image->header->size;
    rotated_image->header->reserved1= image->header->reserved1;
    rotated_image->header->reserved2 = image->header->reserved2;
    rotated_image->header->offset = image->header->offset;
    rotated_image->header->dib_size = image->header->dib_size;
    rotated_image->header->width = image->header->width;
    rotated_image->header->height= image->header->height;
    rotated_image->header->planes = image->header->planes;
    rotated_image->header->bpp= image->header->bpp;
    rotated_image->header->compression = image->header->compression;
    rotated_image->header->image_size = image->header->image_size;
    rotated_image->header->x_ppm= image->header->x_ppm;
    rotated_image->header->y_ppm = image->header->y_ppm;
    rotated_image->header->num_colors = image->header->num_colors;
    rotated_image->header->important_colors = image->header->important_colors;

    struct pixel **niga = calloc(image->header->height, sizeof(struct pixel**));
    if (niga == NULL) {
        //free(arr);
        free_bmp_image(rotated_image);
        return NULL;
    }
    for (uint32_t i = 0; i < image->header->height; ++i) {
        //arr[i] = calloc(image->header->width, sizeof(struct pixel*));
        niga[i] = calloc(image->header->width, sizeof(struct pixel*));
        if (niga[i] == NULL) {
            //free_arrays(arr, image->header->height);
            free_arrays(niga, image->header->height);
            free_bmp_image(rotated_image);
            return NULL;
        }
    }

    struct pixel **arr = one_to_two(image->data, image->header);
    if (arr == NULL) {
        free_arrays(arr, image->header->height);
        free_arrays(niga, image->header->height);
        free_bmp_image(rotated_image);
        return NULL;
    }
    // ****** copy arr to niga
    for (uint32_t i = 0; i < image->header->height; ++i)
        for (uint32_t j = 0; j < image->header->width; ++j)
            niga[i][j] = arr[i][j];

    // ****** transform image there
    for (uint32_t i = 0, ix = image->header->height-1; i < image->header->height; ++i, --ix)
        for (uint32_t j = 0; j < image->header->width; ++j)
            arr[i][j] = niga[ix][j];

    rotated_image->data = two_to_one(arr, image->header->height, image->header->width);

    free_arrays(arr, image->header->height);
    free_arrays(niga, image->header->height);

    return rotated_image;
}


struct bmp_image* rotate_right(const struct bmp_image* image) {
    // ****** null check
    if (image == NULL || image->data == NULL) return NULL;

    // ****** memory allocation for a new picture
    struct bmp_image* rotated_image = calloc(1, sizeof(struct bmp_image));
    if (rotated_image == NULL) return NULL;

    rotated_image->header = malloc(sizeof(struct bmp_header));
    uint32_t width = image->header->height;
    uint32_t height = image->header->width;

    rotated_image->header->type = image->header->type;
    rotated_image->header->size = image->header->size;
    rotated_image->header->reserved1= image->header->reserved1;
    rotated_image->header->reserved2 = image->header->reserved2;
    rotated_image->header->offset = image->header->offset;
    rotated_image->header->dib_size = image->header->dib_size;
    rotated_image->header->width = width;
    rotated_image->header->height= height;
    rotated_image->header->planes = image->header->planes;
    rotated_image->header->bpp= image->header->bpp;
    rotated_image->header->compression = image->header->compression;
    rotated_image->header->image_size = image->header->image_size;
    rotated_image->header->x_ppm= image->header->x_ppm;
    rotated_image->header->y_ppm = image->header->y_ppm;
    rotated_image->header->num_colors = image->header->num_colors;
    rotated_image->header->important_colors = image->header->important_colors;

    uint32_t bpp = rotated_image->header->bpp / 8;
    if ((bpp * width) % 4 != 0)
        rotated_image->header->image_size = ((4 - (bpp * width) % 4) + width * bpp) * rotated_image->header->height;
    else
        rotated_image->header->image_size = width * bpp * rotated_image->header->height;
    rotated_image->header->size = rotated_image->header->image_size + rotated_image->header->offset;

    struct pixel **niga = calloc(image->header->width, sizeof(struct pixel**));
    if (niga == NULL) {
        //free(arr);
        free_bmp_image(rotated_image);
        return NULL;
    }

    for (uint32_t i = 0; i < image->header->width; ++i) {
        niga[i] = calloc(image->header->height, sizeof(struct pixel*));
        if (niga[i] == NULL) {
            free_arrays(niga, image->header->width);
            free_bmp_image(rotated_image);
            return NULL;
        }
    }

    struct pixel **arr = one_to_two(image->data, image->header);
    if (arr == NULL) {
        free_arrays(arr, image->header->height);
        free_arrays(niga, image->header->height);
        free_bmp_image(rotated_image);
        return NULL;
    }
    // ****** copy arr to niga
    for (uint32_t i = 0, ix = image->header->width-1; i < image->header->width; ++i, --ix)
        for (uint32_t j = 0; j < image->header->height; ++j)
            niga[i][j] = arr[j][ix];

    rotated_image->data = two_to_one(niga, rotated_image->header->height, rotated_image->header->width);

    free_arrays(arr, image->header->height);
    free_arrays(niga, image->header->width);

    return rotated_image;
}


struct bmp_image* rotate_left(const struct bmp_image* image) {
    // ****** null check
    if (image == NULL || image->data == NULL || image->header == NULL) return NULL;

    // ****** memory allocation for a new picture
    struct bmp_image* rotated_image = calloc(1, sizeof(struct bmp_image));
    if (rotated_image == NULL) return NULL;

    rotated_image->header = calloc(1, sizeof(struct bmp_header));
    uint32_t width = image->header->height;
    uint32_t height = image->header->width;

    rotated_image->header->type = image->header->type;
    rotated_image->header->size = image->header->size;
    rotated_image->header->reserved1= image->header->reserved1;
    rotated_image->header->reserved2 = image->header->reserved2;
    rotated_image->header->offset = image->header->offset;
    rotated_image->header->dib_size = image->header->dib_size;
    rotated_image->header->width = image->header->width;
    rotated_image->header->height= image->header->height;
    rotated_image->header->planes = image->header->planes;
    rotated_image->header->bpp = image->header->bpp;
    rotated_image->header->compression = image->header->compression;
    rotated_image->header->image_size = image->header->image_size;
    rotated_image->header->x_ppm= image->header->x_ppm;
    rotated_image->header->y_ppm = image->header->y_ppm;
    rotated_image->header->num_colors = image->header->num_colors;
    rotated_image->header->important_colors = image->header->important_colors;

    rotated_image->header->width = width;
    rotated_image->header->height = height;

    uint32_t bpp = image->header->bpp / (uint32_t)8;
    if ((bpp * width) % 4 != 0)
        rotated_image->header->image_size = ((4 - (bpp * width) % 4) + width * bpp) * height;
    else
        rotated_image->header->image_size = width * height * bpp;

    rotated_image->header->size = rotated_image->header->image_size + rotated_image->header->offset;

    struct pixel **niga = calloc(image->header->width, sizeof(struct pixel**));
    if (niga == NULL) {
        free_bmp_image(rotated_image);
        free_arrays(niga, image->header->width);
        return NULL;
    }
    struct pixel **help_array = calloc(image->header->width, sizeof(struct pixel**));
    if (help_array == NULL) {
        free_bmp_image(rotated_image);
        free_arrays(niga, image->header->width);
        return NULL;
    }

    for (uint32_t i = 0; i < image->header->width; ++i) {
        niga[i] = calloc(image->header->height, sizeof(struct pixel*));
        if (niga[i] == NULL) {
            free_arrays(niga, image->header->width);
            free_arrays(help_array, image->header->width);
            free_bmp_image(rotated_image);
            return NULL;
        }
        help_array[i] = calloc(image->header->height, sizeof(struct pixel*));
        if (help_array[i] == NULL) {
            free_arrays(niga, image->header->width);
            free_arrays(help_array, image->header->width);
            free_bmp_image(rotated_image);
            return NULL;
        }
    }

    struct pixel **arr = one_to_two(image->data, image->header);
    if (arr == NULL) {
        free_arrays(niga, image->header->width);
        free_arrays(help_array, image->header->width);
        free_arrays(arr, image->header->height);
        free_bmp_image(rotated_image);
        return NULL;
    }
    // ****** copy arr to niga
    for (uint32_t i = 0, ix = image->header->width-1; i < image->header->width; ++i, --ix) {
        for (uint32_t j = 0; j < image->header->height; ++j) {
            niga[i][j] = arr[j][ix];
            help_array[i][j] = arr[j][ix];
        }
    }
    // ****** transformations image
    for (uint32_t i = 0, ix = height-1; i < height; ++i, --ix) {
        for (uint32_t j = 0, jx = width-1; j < width; ++j, --jx) {
            niga[i][j] = help_array[ix][jx];
        }
    }

    rotated_image->data = two_to_one(niga, rotated_image->header->height, rotated_image->header->width);

    // ***** free memory
    free_arrays(arr, image->header->height);
    free_arrays(niga, image->header->width);
    free_arrays(help_array, image->header->width);

    return rotated_image;
}


struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width) {
    if (image == NULL) return NULL;
    if (image->data == NULL || image->header == NULL) return NULL;
    if (start_x + width > image->header->width || start_y + height > image->header->height) return NULL;
    if (start_x < 0 || start_x > image -> header -> width) return NULL;
    if (start_y < 0 || start_y > image -> header -> height) return NULL;
    if (width <= 0 || start_x + width > image -> header -> width) return NULL;
    if (height <= 0 || start_y + height > image -> header -> height) return NULL;

    struct pixel **array = one_to_two(image->data, image->header);
    if (array == NULL) {
        free_arrays(array, image->header->height);
        return NULL;
    }

    // cat
    struct pixel **cat = calloc(height, sizeof(struct pixel **));
    if (cat == NULL) {
        free_arrays(array, image->header->height);
        return NULL;
    }
    for (uint32_t i = 0; i < height; ++i) {
        cat[i] = calloc(width, sizeof(struct pixel *));
        if (cat[i] == NULL) {
            free_arrays(cat, height);
            free_arrays(array, image->header->height);
            return NULL;
        }
    }

    // main code
    for (uint32_t i = start_x, ix = 0; i < start_x+height; ++i, ++ix) {
        for (uint32_t j = start_y, jx = 0; j < start_y+width; ++j, ++jx) {
            cat[ix][jx] = array[i][j];
        }
    }

    // struct of res picture
    struct bmp_image* picture = calloc(1, sizeof(struct bmp_image));
    if (picture == NULL) {
        free_arrays(array, image->header->height);
        free_arrays(cat, height);
        return NULL;
    }
    picture->header = calloc(1, sizeof(struct bmp_header));

    uint32_t bpp = image->header->bpp / 8, pr = 0;
    if ((bpp * width) % 4 != 0) pr = 4 - (bpp*width) % 4;

    picture->header->type = image->header->type;
    picture->header->reserved1 = image->header->reserved1;
    picture->header->reserved2 = image->header->reserved2;
    picture->header->offset = image->header->offset;
    picture->header->dib_size = image->header->dib_size;
    picture->header->planes = image->header->planes;
    picture->header->bpp = image->header->bpp;
    picture->header->compression = image->header->compression;
    picture->header->image_size = (((width * bpp) + pr) * height)+54;
    picture->header->x_ppm = image->header->x_ppm;
    picture->header->y_ppm = image->header->y_ppm;
    picture->header->num_colors = image->header->num_colors;
    picture->header->important_colors = image->header->important_colors;
    picture->header->size = picture->header->image_size + picture->header->offset;
    picture->header->width = width;
    picture->header->height = height;

    picture->data = two_to_one(cat, height, width);

    free_arrays(array, image->header->height);
    free_arrays(cat, height);
    return picture;
}


struct bmp_image* scale(const struct bmp_image* image, float factor){
    if (image == NULL) return NULL;
    if (image->data == NULL || image->header == NULL) return NULL;
    if (factor <= 0) return NULL;

    // ****** allocate memory for the new picture
    struct bmp_image* picture = calloc(1, sizeof(struct bmp_image));
    if (picture == NULL) return NULL;

    // ****** header for picture
    picture->header = calloc(1, sizeof(struct bmp_header));
    uint32_t new_height = (uint32_t) round((float) image->header->height * factor);
    uint32_t new_width = (uint32_t) round((float) image->header->width * factor);

    picture->header->type = image->header->type;
    picture->header->size = image->header->size;
    picture->header->reserved1= image->header->reserved1;
    picture->header->reserved2 =image->header->reserved2;
    picture->header->offset = image->header->offset;
    picture->header->dib_size = image->header->dib_size;
    picture->header->width = new_width;
    picture->header->height = new_height;
    picture->header->planes = image->header->planes;
    picture->header->bpp = image->header->bpp;
    picture->header->compression = image->header->compression;
    picture->header->image_size = image->header->image_size;
    picture->header->x_ppm = image->header->x_ppm;
    picture->header->y_ppm = image->header->y_ppm;
    picture->header->num_colors = image->header->num_colors;
    picture->header->important_colors = image->header->important_colors;

    uint32_t bpp = image -> header->bpp / 8;
    if ((bpp * new_width) % 4 != 0)
        picture->header->image_size = ((4 - (bpp * new_width) % 4) + new_width * bpp) * new_height;
    else
        picture->header->image_size = new_width * bpp * new_height;
    picture->header->size = picture->header->image_size + picture->header->offset;

    // ***** data for picture
    struct pixel **array = one_to_two(image->data, image->header);
    if (array == NULL) {
        free_bmp_image(picture);
        return NULL;
    }

    struct pixel **picture_arr = calloc(new_height, sizeof(struct pixel **));
    if (picture_arr == NULL) {
        free_bmp_image(picture);
        return NULL;
    }
    for (int i = 0; i < new_height; ++i) {
        picture_arr[i] = calloc(new_width, sizeof(struct pixel *));
        if (picture_arr[i] == NULL) {
            free_arrays(picture_arr, new_height);
            free_bmp_image(picture);
            return NULL;
        }
    }

    // ***** main code

    for (uint32_t i = 0; i < new_height; ++i) {
        uint32_t ix = (i * image->header->height) / new_height;
        for (uint32_t j = 0; j < new_width; ++j) {
            uint32_t jx = (j * image->header->width) / new_width;
            picture_arr[i][j] = array[ix][jx];
            //printf("ix: %d, jx: %d\n", ix, jx);
        }
    }

    picture->data = two_to_one(picture_arr, new_height, new_width);

    free_arrays(picture_arr, new_height);
    free_arrays(array, image->header->height);

    return picture;
}


struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep) {

    // ***** check null
    if (image == NULL) return NULL;
    if (image->data == NULL || image->header == NULL) return NULL;
    if (colors_to_keep == NULL) return NULL;

    bool r = false, g = false, b = false;

    for (int i = 0; colors_to_keep[i] != '\0'; ++i)
    {
        if (colors_to_keep[i] != 'r' && colors_to_keep[i] != 'g' && colors_to_keep[i] != 'b') return NULL;
        else if (colors_to_keep[i] == 'r') r = true;
        else if (colors_to_keep[i] == 'g') g = true;
        else if (colors_to_keep[i] == 'b') b = true;
    }

    // ***** create new picture
    struct bmp_image* picture = calloc(1, sizeof(struct bmp_image));
    if (picture == NULL) return NULL;

    // ****** copy .header for a new picture struct
    picture->header = calloc(1, sizeof(struct bmp_header));
    picture->header->type = image->header->type;
    picture->header->size = image->header->size;
    picture->header->reserved1= image->header->reserved1;
    picture->header->reserved2 = image->header->reserved2;
    picture->header->offset = image->header->offset;
    picture->header->dib_size = image->header->dib_size;
    picture->header->width = image->header->width;
    picture->header->height= image->header->height;
    picture->header->planes = image->header->planes;
    picture->header->bpp= image->header->bpp;
    picture->header->compression = image->header->compression;
    picture->header->image_size = image->header->image_size;
    picture->header->x_ppm= image->header->x_ppm;
    picture->header->y_ppm = image->header->y_ppm;
    picture->header->num_colors = image->header->num_colors;
    picture->header->important_colors = image->header->important_colors;

    // ****** make .data for a new picture struct
    struct pixel **array = one_to_two(image->data, image->header);
    if (array == NULL) {
        free_bmp_image(picture);
        return NULL;
    }
    struct pixel **altered_image = calloc(image->header->height, sizeof(struct pixel**));
    if (altered_image == NULL) {
        free_bmp_image(picture);
        free_arrays(array, image->header->height);
        return NULL;
    }
    for (uint32_t i = 0; i < image->header->height; ++i) {
        altered_image[i] = calloc(image->header->width, sizeof(struct pixel*));
        if (altered_image[i] == NULL) {
            free_bmp_image(picture);
            free_arrays(altered_image, image->header->height);
            return NULL;
        }
    }

    // ***** major changes
    for (uint32_t i = 0; i < image->header->height; ++i) {
        for (uint32_t j = 0; j < image->header->width; ++j) {
            if (r) altered_image[i][j].red = array[i][j].red;
            if (g) altered_image[i][j].green = array[i][j].green;
            if (b) altered_image[i][j].blue = array[i][j].blue;
        }
    }

    picture->data = two_to_one(altered_image, image->header->height, image->header->width);

    free_arrays(array, image->header->height);
    free_arrays(altered_image, image->header->height);

    return picture;
}


void free_arrays (struct pixel ** array, const uint32_t h) {
    for (uint32_t i = 0; i < h; ++i) free(array[i]);
    free(array);
}


struct pixel** one_to_two (const struct pixel* data, const struct bmp_header* header) {
    // ****** null check
    if (data == NULL || header == NULL) return NULL;

    // ****** memory allocation
    struct pixel** image = calloc(header->height, sizeof(struct pixel**));
    if (image == NULL) return NULL;

    for (uint32_t i = 0; i < header->height; ++i) {
        image[i] = calloc(header->width, sizeof(struct pixel*));
        if (image[i] == NULL) {
            free_arrays(image, header->height);
            return NULL;
        }
    }

    for (uint32_t row = 0; row < header->height; ++row) {
        for (uint32_t column = 0; column < header->width; column++) {
            image[row][column].blue = data[(row * header->width) + column].blue;
            image[row][column].red = data[(row * header->width) + column].red;
            image[row][column].green = data[(row * header->width) + column].green;
        }
    }
    return image;
}

struct pixel* two_to_one (struct pixel **image, const uint32_t height, const uint32_t width) {
    if (image == NULL) return NULL;

    struct pixel* imagePixels = calloc(height * width, sizeof(struct pixel*));
    if (imagePixels == NULL) return NULL;

    for (uint32_t row = 0; row < height; ++row) {
        for (uint32_t column = 0; column < width; column++) {
            imagePixels[(row * width) + column].green = image[row][column].green;
            imagePixels[(row * width) + column].red = image[row][column].red;
            imagePixels[(row * width) + column].blue = image[row][column].blue;
        }
    }

    return imagePixels;
}

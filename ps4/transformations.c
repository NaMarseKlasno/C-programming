#include "bmp.h"
#include <stdlib.h>
#include "math.h"

struct bmp_image* crop(const struct bmp_image* image, const int start_y, const int start_x, const int height, const int width){
    if(image==NULL){
        return NULL;
    }
    if(image -> header==NULL){
        return NULL;
    }
    if(image -> data==NULL){
        return NULL;
    }
    if(start_x < 0 || start_x > image -> header -> width) {
        return NULL;
    }
    if(start_y < 0 || start_y > image -> header -> height) {
        return NULL;
    }
    if(width <= 0 || start_x + width > image -> header -> width) {
        return NULL;
    }
    if(height <= 0 || start_y + height > image -> header -> height) {
        return NULL;
    }
    struct bmp_image * new_bmp = malloc(sizeof(struct bmp_image));
    new_bmp -> data = NULL;

    uint32_t old_width=image ->header-> width;
    //uint32_t old_height=image -> header -> height;
    new_bmp -> header = malloc(sizeof(struct bmp_header));
    uint32_t bpp = image -> header -> bpp/8;
    uint32_t pad = (bpp*(uint32_t)width)%4==0?0:4-(bpp*(uint32_t)width)%4;
    new_bmp -> header -> type = image -> header -> type;
    new_bmp -> header -> reserved1 = image -> header -> reserved1;
    new_bmp -> header -> reserved2 = image -> header -> reserved2;
    new_bmp -> header -> offset = image -> header -> offset;
    new_bmp -> header -> dib_size = image -> header -> dib_size;
    new_bmp -> header -> width = (uint32_t) width;
    new_bmp -> header -> height = (uint32_t) height;
    new_bmp -> header -> planes = image -> header -> planes;
    new_bmp -> header -> bpp = image -> header -> bpp;
    new_bmp -> header -> compression = image -> header -> compression;
    new_bmp -> header -> image_size = (pad + (uint32_t)width*bpp)*(uint32_t)height;
    new_bmp -> header -> x_ppm = image -> header -> x_ppm;
    new_bmp -> header -> y_ppm = image -> header -> y_ppm;
    new_bmp -> header -> num_colors = image -> header -> num_colors;
    new_bmp -> header -> important_colors = image -> header -> important_colors;
    new_bmp -> header -> size = new_bmp -> header ->image_size + new_bmp -> header ->offset;
    struct pixel* pixels = malloc(sizeof(struct pixel)*(uint32_t)(height*width));
    //uint32_t ct = (uint32_t)start_x*bpp + (uint32_t)start_y*(bpp*(uint32_t)(width + width%4));
    for(uint32_t y =0; y < height; y++) {
        for(uint32_t z = 0; z < width; z ++) {
            pixels[((height-y-1)*width)+z].red = image -> data[(y*old_width+start_x)+z+start_y].red;
            pixels[((height-y-1)*width)+z].green = image -> data[(y*old_width+start_x)+z+start_y].green;
            pixels[((height-y-1)*width)+z].blue = image -> data[(y*old_width+start_x)+z+start_y].blue;
            //pixels[(y*(uint32_t)width)+z] = image -> data[(y*old_width) + z];
        }
    }
    new_bmp ->data = pixels;
    return  new_bmp;
}
struct bmp_image* flip_horizontally(const struct bmp_image* image){
    if(image==NULL){
        return NULL;
    }
    struct bmp_image * new_bmp = malloc(sizeof(struct bmp_image));
    new_bmp -> header = malloc(sizeof(struct bmp_header));
    new_bmp -> header -> type = image -> header->type;
    new_bmp -> header -> size = image -> header->size;
    new_bmp -> header -> reserved1= image -> header->reserved1;
    new_bmp -> header ->reserved2 = image -> header->reserved2;
    new_bmp -> header ->offset = image -> header->offset;
    new_bmp -> header ->dib_size = image -> header->dib_size;
    new_bmp -> header ->width = image -> header->width;
    new_bmp -> header -> height= image -> header->height;
    new_bmp -> header ->planes = image -> header->planes;
    new_bmp -> header -> bpp= image -> header->bpp;
    new_bmp -> header ->compression = image -> header->compression;
    new_bmp -> header ->image_size = image -> header->image_size;
    new_bmp -> header -> x_ppm= image -> header->x_ppm;
    new_bmp -> header ->y_ppm = image -> header->y_ppm;
    new_bmp -> header ->num_colors = image -> header->num_colors;
    new_bmp -> header ->important_colors = image -> header->important_colors;
    uint32_t height=image -> header -> height;
    uint32_t width=image -> header -> width;
    struct pixel* pixels = malloc(sizeof(struct pixel)*height*width);
    for (uint32_t y = 0; y < height; y++){
        for(uint32_t z = 0;z<width;z++){
            pixels[(y*width)+z].red=image -> data[(y*width)+width-z-1].red;
            pixels[(y*width)+z].green=image -> data[(y*width)+width-z-1].green;
            pixels[(y*width)+z].blue=image -> data[(y*width)+width-z-1].blue;
            //pixels[(y*width)+z]=image -> data[(y*width)+width-z-1];
        }
    }
    new_bmp -> data =pixels;
    return new_bmp;
}

struct bmp_image* flip_vertically(const struct bmp_image* image){
    if(image==NULL){
        return NULL;
    }
    struct bmp_image * new_bmp = malloc(sizeof(struct bmp_image));
    new_bmp -> header = malloc(sizeof(struct bmp_header));
    new_bmp -> header -> type = image -> header->type;
    new_bmp -> header -> size = image -> header->size;
    new_bmp -> header -> reserved1= image -> header->reserved1;
    new_bmp -> header ->reserved2 = image -> header->reserved2;
    new_bmp -> header ->offset = image -> header->offset;
    new_bmp -> header ->dib_size = image -> header->dib_size;
    new_bmp -> header ->width = image -> header->width;
    new_bmp -> header -> height= image -> header->height;
    new_bmp -> header ->planes = image -> header->planes;
    new_bmp -> header -> bpp= image -> header->bpp;
    new_bmp -> header ->compression = image -> header->compression;
    new_bmp -> header ->image_size = image -> header->image_size;
    new_bmp -> header -> x_ppm= image -> header->x_ppm;
    new_bmp -> header ->y_ppm = image -> header->y_ppm;
    new_bmp -> header ->num_colors = image -> header->num_colors;
    new_bmp -> header ->important_colors = image -> header->important_colors;
    uint32_t height=image -> header -> height;
    uint32_t width=image -> header -> width;
    struct pixel* pixels = malloc(sizeof(struct pixel)*height*width);
    for (uint32_t y = 0; y < height; y++){
        for(uint32_t z = 0;z<width;z++){
            pixels[(y*width)+z].red=image -> data[((height-y-1)*width)+z].red;
            pixels[(y*width)+z].green=image -> data[((height-y-1)*width)+z].green;
            pixels[(y*width)+z].blue=image -> data[((height-y-1)*width)+z].blue;
            //pixels[(y*width)+z]=image -> data[(y*width)+width-z-1];
        }
    }
    new_bmp -> data =pixels;
    return new_bmp;
}
//pixels[(y*width)+z].red=image -> data[((width-y-1)*width)+z].red;
//pixels[(y*width)+z].green=image -> data[((width-y-1)*width)+z].green;
//pixels[(y*width)+z].blue=image -> data[((width-y-1)*width)+z].blue;
//pixels[(y*width)+z]=image -> data[((width-y-1)*width)+z];

struct bmp_image* rotate_left(const struct bmp_image* image){
    if(image==NULL){
        return NULL;
    }
    struct bmp_image * new_bmp = malloc(sizeof(struct bmp_image));
    new_bmp -> header = malloc(sizeof(struct bmp_header));
    new_bmp -> header -> type = image -> header->type;
    new_bmp -> header -> size = image -> header->size;
    new_bmp -> header -> reserved1= image -> header->reserved1;
    new_bmp -> header ->reserved2 = image -> header->reserved2;
    new_bmp -> header ->offset = image -> header->offset;
    new_bmp -> header ->dib_size = image -> header->dib_size;
    new_bmp -> header ->width = image -> header->width;
    new_bmp -> header -> height= image -> header->height;
    new_bmp -> header ->planes = image -> header->planes;
    new_bmp -> header -> bpp= image -> header->bpp;
    new_bmp -> header ->compression = image -> header->compression;
    new_bmp -> header ->image_size = image -> header->image_size;
    new_bmp -> header -> x_ppm= image -> header->x_ppm;
    new_bmp -> header ->y_ppm = image -> header->y_ppm;
    new_bmp -> header ->num_colors = image -> header->num_colors;
    new_bmp -> header ->important_colors = image -> header->important_colors;
    uint32_t width=image -> header -> height;
    uint32_t height=image -> header -> width;
    new_bmp -> header -> width=width;
    new_bmp -> header -> height =height;
    uint32_t bpp = new_bmp -> header -> bpp / (uint32_t)8;
    uint32_t pad = (bpp * width) % 4 == 0?0 : 4 - (bpp*width)%4;
    uint32_t image_size =(pad + width*bpp)*new_bmp -> header -> height;
    new_bmp -> header ->image_size=image_size;
    new_bmp -> header -> size = image_size + new_bmp -> header ->offset;
    struct pixel* pixels = malloc(sizeof(struct pixel)*height*width);
    for (uint32_t y = 0; y < height; y++){
        for(uint32_t z = 0;z<width;z++){
            pixels[(y*width)+width-z-1].red=image -> data[(z*height)+y].red;
            pixels[(y*width)+width-z-1].green=image -> data[(z*height)+y].green;
            pixels[(y*width)+width-z-1].blue=image -> data[(z*height)+y].blue;
            //pixels[(z*height)+y]=image -> data[(y*width)+width-z];
        }
    }
    new_bmp -> data =pixels;

    return new_bmp;
}
struct bmp_image* rotate_right(const struct bmp_image* image){
    if(image==NULL){
        return NULL;
    }
    struct bmp_image * new_bmp = malloc(sizeof(struct bmp_image));
    new_bmp -> header = malloc(sizeof(struct bmp_header));
    new_bmp -> header -> type = image -> header->type;
    new_bmp -> header -> size = image -> header->size;
    new_bmp -> header -> reserved1= image -> header->reserved1;
    new_bmp -> header ->reserved2 = image -> header->reserved2;
    new_bmp -> header ->offset = image -> header->offset;
    new_bmp -> header ->dib_size = image -> header->dib_size;
    new_bmp -> header ->width = image -> header->width;
    new_bmp -> header -> height= image -> header->height;
    new_bmp -> header ->planes = image -> header->planes;
    new_bmp -> header -> bpp= image -> header->bpp;
    new_bmp -> header ->compression = image -> header->compression;
    new_bmp -> header ->image_size = image -> header->image_size;
    new_bmp -> header -> x_ppm= image -> header->x_ppm;
    new_bmp -> header ->y_ppm = image -> header->y_ppm;
    new_bmp -> header ->num_colors = image -> header->num_colors;
    new_bmp -> header ->important_colors = image -> header->important_colors;
    uint32_t width=image -> header -> height;
    uint32_t height=image -> header -> width;
    new_bmp -> header -> width=width;
    new_bmp -> header -> height =height;
    uint32_t bpp = new_bmp -> header -> bpp / (uint32_t)8;
    uint32_t pad = (bpp * width) % 4 == 0?0 : 4 - (bpp*width)%4;
    uint32_t image_size =(pad + width*bpp)*new_bmp -> header -> height;
    new_bmp -> header ->image_size=image_size;
    new_bmp -> header -> size = image_size + new_bmp -> header ->offset;
    struct pixel* pixels = malloc(sizeof(struct pixel)*height*width);
    for (uint32_t y = 0; y < height; y++){
        for(uint32_t z = 0;z<width;z++){
            pixels[(y*width)+z].red=image -> data[(z*height)+height-y-1].red;
            pixels[(y*width)+z].green=image -> data[(z*height)+height-y-1].green;
            pixels[(y*width)+z].blue=image -> data[(z*height)+height-y-1].blue;
            //pixels[(z*height)+y]=image -> data[(y*width)+width-z];
        }
    }
    new_bmp -> data =pixels;

    return new_bmp;
}

struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep){
    if(image==NULL){
        return NULL;
    }
    if(image->data==NULL){
        return NULL;
    }

    if(colors_to_keep==NULL){
        return NULL;
    }
    bool red=false;
    bool green=false;
    bool blue=false;
    bool isBlank=true;
    for(;*colors_to_keep;colors_to_keep++){


        if(*colors_to_keep=='r'){
            isBlank=false;
            if(red==true){
                return NULL;
            }
            red = true;
            continue;
        }
        if(*colors_to_keep=='g'){
            isBlank=false;
            if(green==true){
                return NULL;
            }
            green = true;
            continue;
        }
        if(*colors_to_keep=='b'){
            isBlank=false;
            if(blue==true){
                return NULL;
            }
            blue = true;
            continue;
        }
        return NULL;
    }
    if(isBlank){
        return NULL;
    }
    struct bmp_image * new_bmp = malloc(sizeof(struct bmp_image));
    new_bmp -> header = malloc(sizeof(struct bmp_header));
    new_bmp -> header = image -> header;
    uint32_t width=image -> header -> width;
    uint32_t height=image -> header -> height;
    new_bmp -> header -> width=width;
    new_bmp -> header -> height =height;
    struct pixel* pixels = malloc(sizeof(struct pixel)*height*width);
    for (uint32_t y = 0; y < height; y++){
        for(uint32_t z = 0;z<width;z++){
            if(red){
                pixels[(z*height)+y].red=image -> data[(z*height)+y].red;
            }
            else{
                pixels[(z*height)+y].red=0;
            }
            if(green){
                pixels[(z*height)+y].green=image -> data[(z*height)+y].green;
            }
            else{
                pixels[(z*height)+y].green=0;
            }
            if(blue){
                pixels[(z*height)+y].blue=image -> data[(z*height)+y].blue;
            }
            else{
                pixels[(z*height)+y].blue=0;
            }
        }
    }
    new_bmp -> data =pixels;
    return new_bmp;

}

struct bmp_image* scale(const struct bmp_image* image, float factor){
    if(image == NULL){
        return NULL;
    }
    if(image -> data == NULL){
        return NULL;
    }
    if(image -> header == NULL){
        return NULL;
    }
    if(factor<=0){
        return NULL;
    }
    struct bmp_image * new_bmp = malloc(sizeof(struct bmp_image));
    new_bmp -> header = malloc(sizeof(struct bmp_header));
    new_bmp -> header -> type = image -> header->type;
    new_bmp -> header -> size = image -> header->size;
    new_bmp -> header -> reserved1= image -> header->reserved1;
    new_bmp -> header ->reserved2 = image -> header->reserved2;
    new_bmp -> header ->offset = image -> header->offset;
    new_bmp -> header ->dib_size = image -> header->dib_size;
    new_bmp -> header ->width = image -> header->width;
    new_bmp -> header -> height= image -> header->height;
    new_bmp -> header ->planes = image -> header->planes;
    new_bmp -> header -> bpp= image -> header->bpp;
    new_bmp -> header ->compression = image -> header->compression;
    new_bmp -> header ->image_size = image -> header->image_size;
    new_bmp -> header -> x_ppm= image -> header->x_ppm;
    new_bmp -> header ->y_ppm = image -> header->y_ppm;
    new_bmp -> header ->num_colors = image -> header->num_colors;
    new_bmp -> header ->important_colors = image -> header->important_colors;
    uint32_t height = new_bmp -> header -> height;
    uint32_t width = new_bmp -> header -> width;
    uint32_t new_height = (uint32_t) round((float)height * factor);
    uint32_t new_width =(uint32_t)round((float)width * factor);
    uint32_t bpp = image -> header -> bpp/8;
    uint32_t pad = (bpp*new_width)%4==0?0:4-(bpp*new_width)%4;
    new_bmp -> header -> width=new_width;
    new_bmp -> header -> height=new_height;
    new_bmp -> header -> image_size = (pad + new_width*bpp)*new_height;
    new_bmp -> header -> size = new_bmp -> header ->image_size + new_bmp -> header ->offset;
    struct pixel* pixels = malloc(sizeof(struct pixel)*new_height*new_width);
    for (uint32_t y = 0; y < new_height; y++){
        for(uint32_t z = 0;z<new_width;z++){
            pixels[(y*new_width)+z].red=image -> data[(int)(floor(y/factor)*width+floor(z/factor))].red;
            pixels[(y*new_width)+z].green=image -> data[(int)(floor(y/factor)*width+floor(z/factor))].green;
            pixels[(y*new_width)+z].blue=image -> data[(int)(floor(y/factor)*width+floor(z/factor))].blue;
            //pixels[(y*new_width)+z]=image -> data[(int)(floor((float)y/factor)*width+floor((float)z/factor))];
        }
    }
    new_bmp -> data =pixels;
    return new_bmp;

}

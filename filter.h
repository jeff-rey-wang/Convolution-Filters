#ifdef FILTER_H
#define FILTER_H

typedef struct pixel {
    unsigned char r,g,b;
} Pixel;

typedef struct image {
    unsigned int width, height, max;
    Pixel **data;
} Image;

Image *readPPM(char *file_name);
int writePPM(char *file_name, Image *image);




#endif

#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

namespace imageprocess
{
    void preprocessImage(int width, int height);

    unsigned char* crop(unsigned char* bmp, int width, int height, int new_width, int new_height);
    void resize(unsigned char* bmp, int width, int height, int scale);
    void averageColor(unsigned char* bmp, int width, int height, unsigned char* color);

    bool fileExists(char* path);
}

#endif
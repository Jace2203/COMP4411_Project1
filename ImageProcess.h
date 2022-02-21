#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

namespace imageprocess
{
    void preprocessImage(int width, int height);
    char* averageColor(unsigned char* bmp, int width, int height);

    bool fileExists(char* path);
}

#endif
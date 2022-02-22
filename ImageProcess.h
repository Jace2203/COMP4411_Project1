#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

class ThreeDTree;

namespace imageprocess
{
    void preprocessImage(int width, int height);

    unsigned char* crop(unsigned char* bmp, int width, int height, int new_width, int new_height);
    unsigned char* resize(unsigned char* bmp, int width, int height, int scale, bool scaleup = true);
    void averageColor(unsigned char* bmp, int width, int height, unsigned char* color);

    bool fileExists(char* path);

    ThreeDTree* getProcessedFiles();
    bool sameColor(char* file1, char* file2);

    // char** getFileNames(char* path);
}

#endif
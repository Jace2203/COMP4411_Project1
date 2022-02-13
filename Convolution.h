//
// matrix.h
//
// The header file for convolution
//

#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "Matrix.h"

class Convolution
{
public:
    Convolution(unsigned char* bmp, int width, int height);
    ~Convolution();

    double XGradient(int x, int y);
    double YGradient(int x, int y);

private:
    static Matrix Sobel_X;
    static Matrix Sobel_Y;
    static Matrix Gaussian;

    unsigned char* bmp;
    int width, height;

    void ConvolutionFilter(const Matrix& kernel, int x, int y, bool greyscale, double* color);
};

#endif
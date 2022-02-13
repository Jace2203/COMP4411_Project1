//
// matrix.h
//
// The header file for convolution
//

#include "Matrix.h"

static class Convolution
{
public:
    Convolution();
    ~Convolution();

    double XGradient(unsigned char* bmp, int width, int height, int x, int y);
    double YGradient(unsigned char* bmp, int width, int height, int x, int y);

private:
    Matrix Sobel_X;
    Matrix Sobel_Y;
    Matrix Gaussian;

    void ConvolutionFilter(unsigned char* bmp, int width, int height, Matrix kernel, int x, int y, bool greyscale, double* color);
};
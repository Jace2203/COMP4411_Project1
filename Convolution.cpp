//
// Convolution.cpp
//
// The implementation of Convolution.
//

#include "Convolution.h"

#include <cstdio>

static double sobel_x_values[9] = {
    -1.0, 0.0, 1.0,
    -2.0, 0.0, 2.0,
    -1.0, 0.0, 1.0
};
Matrix Convolution::Sobel_X = Matrix(3, 3, sobel_x_values);

static double sobel_y_values[9] = {
     1.0,  2.0,  1.0,
     0.0,  0.0,  0.0,
    -1.0, -2.0, -1.0
};
Matrix Convolution::Sobel_Y = Matrix(3, 3, sobel_y_values);

static double gaussian_values[9] = {
    1.0, 2.0, 1.0,
    2.0, 4.0, 2.0,
    1.0, 2.0, 1.0
};
Matrix Convolution::Gaussian = Matrix(3, 3, gaussian_values);

Convolution::Convolution(unsigned char* bmp, int width, int height)
: bmp(bmp), width(width), height(height)
{
}

Convolution::~Convolution()
{
}

double Convolution::XGradient(int x, int y)
{
    double color[3] = { 0.0, 0.0, 0.0 };
    ConvolutionFilter(Sobel_X, x, y, true, color);
    return (int)color[0];
}

double Convolution::YGradient(int x, int y)
{
    double color[3] = { 0.0, 0.0, 0.0 };
    ConvolutionFilter(Sobel_Y, x, y, true, color);
    return (int)color[0];
}

void Convolution::ConvolutionFilter(const Matrix& kernel, int x, int y, bool greyscale, double* color)
{
    int w = kernel.getWidth();
    int h = kernel.getHeight();

    double r = 0;
    double g = 0;
    double b = 0;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int rr = 0;
            int gg = 0;
            int bb = 0;
            int xx = x + j - 1;
            int yy = y - i + 1;

            if (xx >= 0 && xx < width && yy >= 0 && yy < height)
            {
                rr = bmp[(yy * width + xx) * 3];
                gg = bmp[(yy * width + xx) * 3 + 1];
                bb = bmp[(yy * width + xx) * 3 + 2];

                if (greyscale)
                {
                    rr = gg = bb = (29.9 * rr + 58.7 * gg + 11.4 * bb) / 100;
                }
            }

            r += rr * kernel.getValue(i, j);
            g += gg * kernel.getValue(i, j);
            b += bb * kernel.getValue(i, j);
        }
    }

    color[0] = r;
    color[1] = g;
    color[2] = b;
}

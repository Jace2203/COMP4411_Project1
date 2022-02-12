//
// Convolution.cpp
//
// The implementation of Convolution.
//

#include "Convolution.h"

Convolution::Convolution()
{
    double sobel_x_values[9] = {
        -1.0, 0.0, 1.0,
        -2.0, 0.0, 2.0,
        -1.0, 0.0, 1.0
    };
    Sobel_X = Matrix(3, 3, sobel_x_values);

    double sobel_y_values[9] = {
         1.0,  2.0,  1.0,
         0.0,  0.0,  2.0,
        -1.0, -2.0, -1.0
    };
    Sobel_Y = Matrix(3, 3, sobel_y_values);

    double gaussian_values[9] = {
        1.0, 2.0, 1.0,
        2.0, 4.0, 2.0,
        1.0, 2.0, 1.0
    };
    Gaussian = Matrix(3, 3, gaussian_values);
}

Convolution::~Convolution()
{
}

double Convolution::XGradient(unsigned char* bmp, int width, int height, int x, int y)
{
    double color[3] = { '\0', '\0', '\0' };
    ConvolutionFilter(bmp, width, height, Sobel_X, x, y, true, color);
    return (int)color[0];
}

void Convolution::ConvolutionFilter(unsigned char* bmp, int width, int height, Matrix kernel, int x, int y, bool greyscale, double* color)
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
                rr = (double)bmp[(yy * w + xx) * 3];
                gg = (double)bmp[(yy * w + xx) * 3 + 1];
                bb = (double)bmp[(yy * w + xx) * 3 + 2];

                if (greyscale)
                {
                    rr = gg = bb = (29.9 * rr + 57.8 * gg + 11.4 * bb) / 100;
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

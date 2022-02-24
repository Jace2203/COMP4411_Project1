#include "Paintly.h"

#include <math.h>

#include "Convolution.h"

Paintly::Paintly()
: m_ucRefImage(NULL), width(0), height(0)
{
}

void Paintly::genRefImage(unsigned char* bmp, int width, int height, int size, double sigma)
{
    this->width = width;
    this->height = height;

    Convolution* con = new Convolution(bmp, width, height);
    Matrix* gaussian = Matrix::GaussianBlurMatrix((size - 1) / 2, sigma);

    if (m_ucRefImage) delete m_ucRefImage;

    m_ucRefImage = new unsigned char[width * height * 3];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double color[3] = { 0.0, 0.0, 0.0 };
            con->ConvolutionFilter(*gaussian, width, height, false, true, color);
            for (int k = 0; k < 3; k++)
            {
                m_ucRefImage[(i * width + j) * 3 + k] = int(color[k]);
            }
        }
    }

    delete gaussian;
    delete con;
}

double Paintly::ColorDiff(int* a, int* b)
{
	int sum = 0;

	for (int i = 0; i < 3; i++)
	{
		sum += (pow((a[i] - b[i]), 2));
	}

	return sqrt(sum);
}
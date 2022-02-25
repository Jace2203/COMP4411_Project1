#include "Paintly.h"

#include <math.h>

#include "Convolution.h"

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "Bitmap.h"

Paintly::Paintly(ImpressionistDoc* pDoc)
: m_ucRefImage(NULL), width(0), height(0), m_pDoc(pDoc), m_pllMax(NULL), tail(NULL)
{
}

Paintly::~Paintly()
{
    delete m_ucRefImage;
    delete m_pllMax;
}

Pointll::Pointll(int x, int y)
{
	xy = Point(x, y);
	next = nullptr;
}

Pointll::~Pointll()
{
	//delete this->next;
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
            con->ConvolutionFilter(*gaussian, j, i, false, true, color);
            for (int k = 0; k < 3; k++)
            {
                m_ucRefImage[(i * width + j) * 3 + k] = int(color[k]);
            }
        }
    }

    delete gaussian;
    delete con;
}

/*
double Paintly::ColorDiff(int* a, int* b)
{
	int sum = 0;

	for (int i = 0; i < 3; i++)
	{
		sum += (pow((a[i] - b[i]), 2));
	}

	return sqrt(sum);
}
*/

void Paintly::DrawPaintly()
{
	std::cout << INT_MAX;

	m_pDoc->setBrushType(2);
	srand(time(NULL));

	glDrawBuffer(GL_FRONT_AND_BACK);

	//unsigned char* canvas = new unsigned char[m_nDrawWidth * m_nDrawHeight * 3];
	//memset (canvas, 0, m_nDrawWidth * m_nDrawHeight * 3);

	unsigned char* sourceImage = m_pDoc->m_ucBitmap;

	int size = pow(2, m_pDoc->m_nPaintlyR0Level + 1);
	//genRefImage(m_pDoc->m_ucBitmap, m_pDoc->m_nPaintWidth, m_pDoc->m_nPaintHeight, size, 0.5);

	// width = m_pDoc->m_nPaintWidth;
	// height = m_pDoc->m_nPaintHeight;
	//m_ucRefImage = m_pDoc->m_ucPainting;

	//genRefImage( m_pDoc->m_ucBitmap, m_pDoc->m_nPaintWidth, m_pDoc->m_nPaintHeight, size);

	m_ucRefImage = readBMP("t.bmp", width, height);

	unsigned char* canvas = new unsigned char[width * height * 3];
	memset(canvas, 0, width * height * 3);
	memset(m_pDoc->m_ucPainting, 0, width * height * 3);

	m_pDoc->m_pUI->m_paintView->draw();

	for (int layer = 0; layer < m_pDoc->m_nPaintlyLayer; ++layer)
	{
		m_nNumMax = 0;
		m_pDoc->setSize(size);

		paintLayer(canvas, m_ucRefImage, size, layer);

		Point* PointList = new Point[m_nNumMax];
		Point temp_pt;
		Pointll* head = m_pllMax;
		int index;
		for(int t = 0; t < m_nNumMax; ++t)
		{
			PointList[t] = head->xy;
			head = head->next;
		}

		for(int t = 0; t < m_nNumMax; ++t)
		{
			index = rand() % m_nNumMax;
			temp_pt = PointList[index];
			PointList[index] = PointList[t];
			PointList[t] = temp_pt;
		}

		for(int t = 0; t < m_nNumMax; ++t)
			m_pDoc->m_pCurrentBrush->BrushMove( PointList[t], PointList[t] );
		glFlush();

		glReadBuffer(GL_BACK);
		glPixelStorei( GL_PACK_ALIGNMENT, 1 );
		glPixelStorei( GL_PACK_ROW_LENGTH, width );
		glReadPixels( 0, 
					0, 
					width, 
					height, 
					GL_RGB, 
					GL_UNSIGNED_BYTE, 
					canvas );
		delete m_pllMax;
		m_pllMax = nullptr;
		delete []PointList;
		size /= 2;
	}

	memcpy(m_pDoc->m_ucPainting, canvas, width * height * 3);
	m_pDoc->m_pUI->m_paintView->redraw();
	printf("finish");
}


void Paintly::paintLayer(unsigned char* canvas, unsigned char* m_ucRefImage, int R, int layer)
{
	double* D = new double[width*height];
	GLubyte color1[3], color2[3];
	double grid = m_pDoc->m_nPaintlyGridSize * R;

	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
		{
			// memcpy(color1, canvas + 3 * (x + y * width), 3);
			// memcpy(color2, m_ucRefImage + 3 * (x + y * width), 3);
			// D[x+y*width] = ColorDiff(color1, color2);
			D[x+y*width] = INT_MAX;
		}

	// if (layer==-1)
	// {
	// 	printf("in");
	// 	unsigned char* TPaint = new unsigned char [width*height*3];
	// 	memset (TPaint, 0, width*height*3);

	// 	glPointSize(m_pDoc->getSize());
	// 	glColor3f(1, 1, 1);

	// 	Pointll* current;

	// 	for (int y = 0; y < height; y += grid / 4)
	// 		for (int x = 0; x < width; x += grid / 4)
	// 		{
	// 			printf("%d %d\n", x, y);
	// 			if (*(GetColor(TPaint, x, y)) == 0)
	// 			{
	// 				AreaError(x, y, grid / 2, D, m_pDoc->m_nPaintlyTheshold);
					
	// 				current = m_pllMax;

	// 				while(current)
	// 				{
	// 					if (*(GetColor(TPaint, current->xy.x, current->xy.y)) == 0)
	// 					{
	// 						glBegin(GL_POINT);
	// 							glVertex2d(current->xy.x, current->xy.y);
	// 						glEnd();
	// 						glFlush();

	// 						glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	// 						glPixelStorei( GL_PACK_ROW_LENGTH, width );
	// 						glReadPixels( 0, 
	// 									0, 
	// 									width, 
	// 									height, 
	// 									GL_RGB, 
	// 									GL_UNSIGNED_BYTE, 
	// 									TPaint );
	// 					}
	// 					current = current->next;
	// 				}
	// 			}
	// 		}

	// 	delete []TPaint;
	// }
	// else

	for (int y = grid/2; y < height; y += grid)
		for (int x = grid/2; x < width; x += grid)
			AreaError(x, y, grid / 2, D, canvas);

	delete []D;
}


void Paintly::makeSplineStroke(int x_0, int y_0, int R, unsigned char* m_ucRefImage)
{
}

void Paintly::AreaError(int x, int y, double grid, double* D, unsigned char* canvas)
{
	int upper_x = (x + grid > width) ? width : x + grid,
		lower_x = (x - grid < 0) ? 0 : x - grid,
		upper_y = (y + grid > height) ? height : y + grid,
		lower_y = (y - grid < 0) ? 0 : y - grid;
	double error = 0;
	double nMax = 0;
	Pointll* temp;
	Point max;

	for(int j = lower_y; j < upper_y; ++j)
		for(int i = lower_x; i < upper_x; ++i)
		{
			error += D[i+j*width];
			if (ColorDiff(canvas + 3*(i+j*width), m_ucRefImage + 3*(i+j*width)) > nMax)
			{
				nMax = ColorDiff(canvas + 3*(i+j*width), m_ucRefImage + 3*(i+j*width));
				max = Point(i, j);
			}
		}

	if (!m_pllMax)
	{
		m_pllMax = new Pointll(max.x, max.y);
		tail = m_pllMax;
	}
	else
	{
		tail->next = new Pointll(max.x, max.y);
		tail = tail->next;
	}
	++m_nNumMax;

	// if (error / (grid * grid * 4) > m_pDoc->m_nPaintlyTheshold)
	// 	for(int j = lower_y; j < upper_y; ++j)
	// 		for(int i = lower_x; i < upper_x; ++i)
	// 		{
	// 			if (D[i+j*width] == nMax)
	// 			{
	// 				if (!m_pllMax)
	// 				{
	// 					m_pllMax = new Pointll(i, j);
	// 					tail = m_pllMax;
	// 				}
	// 				else
	// 				{
	// 					tail->next = new Pointll(i, j);
	// 					tail = tail->next;
	// 				}
	// 				++m_nNumMax;
	// 			}
	// 		}
}

double Paintly::ColorDiff(GLubyte* color1, GLubyte* color2)
{
	return sqrt(pow(*(color1) - *(color2), 2) + pow(*(color1+1) - *(color2+1), 2) + pow(*(color1+2) - *(color2+2), 2));
}

GLubyte* Paintly::GetColor(unsigned char* source, int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= width ) 
		x = width-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= height ) 
		y = height-1;

	return (GLubyte*)(source + 3 * (y*height + x));
}
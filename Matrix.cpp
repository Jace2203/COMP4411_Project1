//
// Matrix.cpp
//
// The implementation of Matrix. Matrix computation for convolution and other matrix operation
//

#include "Matrix.h"

#include <string.h>

Matrix::Matrix()
: elements(nullptr), m(0), n(0)
{
}

Matrix::Matrix(int size)
: m(size), n(size)
{
    elements = new double*[size];
    for (int i = 0; i < size; i++)
    {
        elements[i] = new double[size];
    }

    initialize();
}

Matrix::Matrix(int m, int n)
: m(m), n(n)
{
    elements = new double*[m];
    for (int i = 0; i < m; i++)
    {
        elements[i] = new double[n];
    }

    initialize();
}

Matrix::Matrix(int m, int n, double* values)
: m(m), n(n)
{
    elements = new double*[m];
    for (int i = 0; i < m; i++)
    {
        elements[i] = new double[n];
        memcpy(elements[i], values + i * n, n * sizeof(double));
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < m; i++)
    {
        delete[] elements[i];
    }

    delete[] elements;
}

void Matrix::initialize()
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            elements[i][j] = 0.0;
        }
    }
}

void Matrix::identity(int num = 1)
{
    if (m != n) return;
    
    initialize();
    for (int i = 0; i < m; i++)
    {
        elements[i][i] = num;
    }
}

void Matrix::setValue(int x, int y, int num)
{
    elements[x][y] = num;
}

double Matrix::getValue(int x, int y) const
{
    return elements[x][y];
}

int Matrix::getWidth() const
{
    return n;
}

int Matrix::getHeight() const
{
    return m;
}

double Matrix::InnerSum()
{
    double sum = 0;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            sum += elements[i][j];
        }
    }

    return sum;
}
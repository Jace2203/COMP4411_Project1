//
// matrix.h
//
// The header file for matrix
//

#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
    Matrix();
    Matrix(int size);
    Matrix(int m, int n);
    Matrix(int m, int n, double* values);

    ~Matrix();

    void    initialize();
    void    identity(int num);

    void    setValue(int x, int y, int num);
    double  getValue(int x, int y) const;

    int     getWidth() const;
    int     getHeight() const;

    double  InnerSum();

private:
    int m, n;
    double** elements;
};

#endif
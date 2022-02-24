#ifndef PAINTLY_H
#define PAINTLY_H

class Paintly
{
public:
    Paintly();

    unsigned char* m_ucRefImage;
    
    int width, height;

    void genRefImage(unsigned char* bmp, int width, int height, int size, double sigma = 1.0);

	static double ColorDiff(int* a, int* b);
};

#endif
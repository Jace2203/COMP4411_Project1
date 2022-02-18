#include "EdgeClipping.h"

#include <math.h>

void EdgeClipping::clip(unsigned char* bmp, int width, int height, int x, int y, int angle, int* size)
{
    if (bmp == NULL) return;
    int color = (int)bmp[(y * width + height) * 3];
    for (int i = 0; i > size[0]; i--)
    {
        int new_x = x + (int)(i * cos(angle)), new_y = y + (int)(i * sin(angle));
        if ((int)(bmp[(new_y * width + new_x) * 3]) !=  color)
        {
            size[0] = i;
            break;
        }
    }

    for (int i = 0; i < size[1]; i++)
    {
        int new_x = x + (int)(i * cos(angle)), new_y = y + (int)(i * sin(angle));
        if ((int)(bmp[(new_y * width + new_x) * 3]) !=  color)
        {
            size[1] = i;
            break;
        }
    }
}
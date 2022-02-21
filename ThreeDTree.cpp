#include "ThreeDTree.h"

#include <iostream>
#include <stdio.h>
#include <string.h>

ThreeDTree::Color::Color()
: rgb(NULL)
{
}

ThreeDTree::Color::Color(int r, int g, int b)
{
    rgb = new unsigned char[3];
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
}

// ThreeDTree::Color::Color(char* name)
// {
    
// }

ThreeDTree::Color::Color(unsigned char* color)
{
    rgb = new unsigned char[3];
    memcpy(rgb, color, 3);
}

ThreeDTree::Color::~Color()
{
    delete[] rgb;
}

int ThreeDTree::Color::r() const
{
    return int(rgb[0]);
}

int ThreeDTree::Color::g() const
{
    return int(rgb[1]);
}

int ThreeDTree::Color::b() const
{
    return int(rgb[2]);
}

ThreeDTree::ThreeDTree(Color** colors, int size, RGB rgb)
{
    sortColor(colors, size, rgb);

    for (int i = 0; i < size; i++)
    {
        std::cout << colors[i]->r() << std::endl;
    }
}

void ThreeDTree::sortColor(Color** colors, int size, RGB rgb)
{
    if (size == 1) return;

    int size_l, size_r;
    Color **l = NULL, **r = NULL;

    split(colors, size, size_l, size_r, l, r);

    sortColor(l, size_l, rgb);
    sortColor(r, size_r, rgb);

    merge(colors, size_l, size_r, l, r, rgb);

    delete[] l;
    delete[] r;
}

void ThreeDTree::split(Color** colors, int size, int& size_l, int& size_r, Color** &l, Color** &r)
{
    size_l = floor(double(size) / 2);
    size_r = ceil(double(size) / 2);

    l = new Color*[size_l];
    for (int i = 0; i < size_l; i++)
    {
        l[i] = colors[i];
    }

    r = new Color*[size_r];
    for (int i = 0; i < size_r; i++)
    {
        r[i] = colors[size_l + i];
    }
}

void ThreeDTree::merge(Color** &colors, int size_l, int size_r, Color** l, Color** r, RGB rgb)
{
    int a = 0, b = 0;

    while (a + b < size_l + size_r)
    {
        bool larger = false;
        if (a < size_l && b < size_r)
        {
            switch (rgb)
            {
            case R:
                if (l[a]->r() > r[b]->r()) larger = true;
                break;
            case G:
                if (l[a]->g() > r[b]->g()) larger = true;
                break;
            case B:
                if (l[a]->b() > r[b]->b()) larger = true;
                break;
            default:
                break;
            }
        }
        else if (b < size_l)
        {
            larger = true;
        }

        if (larger)
        {
            colors[a + b] = r[b];
            b++;
        }
        else
        {
            colors[a + b] = l[a];
            a++;
        }
    }
}
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
    Color** sorted_colors = new Color*[size];

    sortColor(colors, sorted_colors, size, rgb);

    for (int i = 0; i < size; i++)
    {
        std::cout << sorted_colors[i]->r() << std::endl;
    }

    // delete[] sorted_colors;
    // idk Y this causing error
}

void ThreeDTree::sortColor(Color** colors, Color** sorted_colors, int size, RGB rgb)
{
    sorted_colors[0] = colors[0];

    for (int i = 1; i < size; i++)
    {
        int head = 0, tail = i - 1;
        int middle = (head + tail) / 2;

        while (head <= tail)
        {
            bool larger = false;
            switch (rgb)
            {
            case R:
                if (colors[i]->r() > sorted_colors[middle]->r())
                    larger = true;
                break;
            case G:
                if (colors[i]->g() > sorted_colors[middle]->g())
                    larger = true;
                break;
            case B:
                if (colors[i]->b() > sorted_colors[middle]->b())
                    larger = true;
                break;
            }

            if (larger)
            {
                head = middle + 1;
                middle = (head + tail) / 2;
            }
            else
            {
                tail = middle - 1;
                middle = (head + tail) / 2;
            }
        }

        if (head > tail)
        {
            for (int j = i; j > middle; j--)
            {
                sorted_colors[j + 1] = sorted_colors[j];
            }

            sorted_colors[middle + 1] = colors[i];
        }
        else
        {
            for (int j = i; j >= middle; j--)
            {
                sorted_colors[j + 1] = sorted_colors[j];
            }

            sorted_colors[middle] = colors[i];
        }
    }
}
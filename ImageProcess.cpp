#include "ImageProcess.h"

#include "dirent/include/dirent.h"
#include "Bitmap.h"

#include <stdio.h>
#include <math.h>
#include <fstream>
#include <sstream>
#include <iomanip>

void imageprocess::preprocessImage(int width, int height)
{
    DIR* dir;
    struct dirent *ent;

    char* path = "images/unprocessed/";
    if ((dir = opendir(path)) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_name[0] != '.')
            {
                unsigned char*	data;
	            int				w, 
					            h;

                char* file_path = new char[strlen(path) + ent->d_namlen + 1];
                strcpy(file_path, path);
                strcat(file_path, ent->d_name);

	            if ( (data=readBMP(file_path , w, h))==NULL ) 
	            {
	            	continue;
	            }

                // do crop
                unsigned char* temp_data = crop(data, w, h, width, height);
                delete[] data;
                data = temp_data;

                // do resize

                char* new_path = "images/processed/";
                char* new_file_path = new char[strlen(new_path) + 18];
                strcpy(new_file_path, new_path);
                unsigned char* colors = new unsigned char[3];
                averageColor(data, width, height, colors);

                std::stringstream ss;
                for (int i = 0; i < 3; i++)
                {
                    ss << std::setfill('0') << std::setw(3) << int(colors[i]);
                }
                strcat(new_file_path, ss.str().c_str());
                strcat(new_file_path, "_000.bmp");

                int count = 0;
                while (fileExists(new_file_path))
                {
                    count++;
                    std::stringstream ss;
                    ss << std::setfill('0') << std::setw(3) << count;
                    char* new_num = new char[4];
                    strcpy(new_num, ss.str().c_str());
                    memcpy(new_file_path + strlen(new_path) + 10, new_num, 3);
                    delete[] new_num;
                }

                writeBMP(new_file_path, width, height, data);
                printf("%s\n", new_file_path);

                // delete[] name;
                delete[] colors;
                delete[] new_file_path;
                delete[] file_path;
                delete[] data;
            }
        }
        closedir(dir);
    }
}

void imageprocess::averageColor(unsigned char* bmp, int width, int height, unsigned char* color)
{
    int r = 0, g = 0, b = 0;
    for (int i = 0; i < width * height; i++)
    {
        r += int(bmp[i * 3]);
        g += int(bmp[i * 3 + 1]);
        b += int(bmp[i * 3 + 2]);
    }
    color[0] = int(r / (width * height));
    color[1] = int(g / (width * height));
    color[2] = int(b / (width * height));
}

unsigned char* imageprocess::crop(unsigned char* bmp, int width, int height, int new_width, int new_height)
{
    int diff_x = width - new_width;
    int diff_y = height - new_height;
    int offset_x = diff_x / 2;
    int offset_y = diff_y / 2;

    unsigned char* new_data = new unsigned char[width * height * 3];

    // Not accpeting smaller image
    if (diff_x >= 0 && diff_y >= 0)
    {
        for (int i = 0; i < height - diff_y; i++)
        {
            memcpy(new_data + (i * width * 3), bmp + (((i + offset_y) * width + offset_x) * 3), 3 * new_width);
        }
    }
    else
    {
        delete[] new_data;
        return NULL;
    }

    return new_data;
}

bool imageprocess::fileExists(char* path)
{
    if (FILE *file = fopen(path, "r"))
    {
        fclose(file);
        return true;
    }
    else
    {
        return false;
    }
}
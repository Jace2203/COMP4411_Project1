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
	            	return;
	            }

                int diff_x = w - width;
                int diff_y = h - height;
                int offset_x = diff_x / 2;
                int offset_y = diff_y / 2;

                unsigned char* new_data = new unsigned char[width * height * 3];

                // Not accpeting smaller image
                if (diff_x >= 0 && diff_y >= 0)
                {
                    for (int i = 0; i < h - diff_y; i++)
                    {
                        memcpy(new_data + (i * width * 3), data + (((i + offset_y) * w + offset_x) * 3), 3 * width);
                    }
                }

                char* new_path = "images/processed/";
                char* new_file_path = new char[strlen(new_path) + 20];
                strcpy(new_file_path, new_path);
                char* name = averageColor(new_data, width, height);
                strcat(new_file_path, name);
                strcat(new_file_path, "_000.bmp");

                int count = 0;
                while (fileExists(new_file_path))
                {
                    count++;
                    std::stringstream ss;
                    ss << std::setfill('0') << std::setw(3) << count;
                    char* new_num = new char[4];
                    strcpy(new_num, ss.str().c_str());
                    memcpy(new_file_path + strlen(new_path) + 12, new_num, 3);
                    delete[] new_num;
                }

                writeBMP(new_file_path, width, height, new_data);
                printf("%s\n", new_file_path);

                // delete[] name;
                delete[] new_file_path;
                delete[] file_path;
                delete[] new_data;
                delete[] data;
            }
        }
        closedir(dir);
    }
}

char* imageprocess::averageColor(unsigned char* bmp, int width, int height)
{
    int r = 0, g = 0, b = 0;
    for (int i = 0; i < width * height; i++)
    {
        r += int(bmp[i * 3]);
        g += int(bmp[i * 3 + 1]);
        b += int(bmp[i * 3 + 2]);
    }
    r = int(r / (width * height));
    g = int(g / (width * height));
    b = int(b / (width * height));
    
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(3) << r << '_' << std::setw(3) << g << '_' << std::setw(3) << b;
    char* name = new char[12];
    strcpy(name, ss.str().c_str());

    return name;
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
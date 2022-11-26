#include <iostream>
#include "triangle.cpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "libs/ImageGenerator/stb_image_write.h"

using namespace std;

void constructRayThroughPixel(int camera, int x, int y, int width, int height)
{
    // float pixelNDCx = (x + 0.5) / width;
    // float pixelNDCy = (y + 0.5) / height;

    // float pixelScreenX = 2 * pixelNDCx - 1;
    // float pixelScreenY = 1 - 2 * pixelNDCy;

    // // for fov 90
    // float tanA = tan(M_PI / 4);

    // float aspectRatio = width / height;
    // float pixelCameraX = (2 * pixelScreenX - 1) * aspectRatio * tanA;
    // float pixelCameraY = (1 - 2 * pixelCameraY) * tanA;
}

void rayCast(unsigned char* image, int width, int height)
{

    Triangle triangleOne;
    Triangle triangleTwo;
    
    triangleOne.intersect();
    
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = (width * y + x) * 3;
            image[index] = 0;
            image[index + 1] = 255;
            image[index + 2] = 127;
        }
    }
}

int main()
{

    const int width = 100;
    const int height = 100;

    unsigned char image[width * height * 3];
    rayCast(image, width, height); // address of a

    // cout<<"Array is: ";
    // for (int i = 0; i < width * height * 3; i++)
    // {
    //     if (i % 3 == 0){
    //         cout << " ";
    //         if ((i / 3) % width == 0)
    //             cout << endl;
    //     }
    //     cout << image[i];
    // }

    stbi_write_bmp("output.bmp", width, height, 3, image);
    return 0;
}
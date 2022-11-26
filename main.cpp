#include <iostream>
#include "libs/glm/glm.hpp"
#include "ray.cpp"
#include "triangle.cpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "libs/ImageGenerator/stb_image_write.h"

using namespace std;

Ray constructRayThroughPixel(int camera, int x, int y, int width, int height)
{
    float pixelNDCx = (x + 0.5) / width;
    float pixelNDCy = (y + 0.5) / height;

    float pixelScreenX = 2 * pixelNDCx - 1;
    float pixelScreenY = 1 - 2 * pixelNDCy;

    // for fov 90
    // float tanA = tan(M_PI / 4);
    float tanA = 1;

    float aspectRatio = width / height;
    float pixelCameraX = (2 * pixelScreenX - 1) * aspectRatio * tanA;
    float pixelCameraY = (1 - 2 * pixelScreenY) * tanA;

    glm::vec3 dir(pixelCameraX, pixelCameraY, -1);
    glm::normalize(dir);
    glm::vec3 orig(0, 0, 0);

    Ray ray(orig, dir);

    return ray;
}

void rayCast(unsigned char *image, int width, int height, Triangle *traingles)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int camera = 0;
            const Ray ray = constructRayThroughPixel(camera, x, y, width, height);

            float t_min = INFINITY;
            for (int i = 0; i < 3; i++)
            {
                const Triangle triangle = traingles[i];

                float t, u, v;
                bool intersects = Triangle::checkIntersection(triangle, ray, t, u, v);

                cout << "test" << endl;
                if (intersects && t_min > t)
                {
                    t_min = t;

                    int index = (width * y + x) * 3;
                    image[index] = triangle.color.x;
                    image[index + 1] = triangle.color.y;
                    image[index + 2] = triangle.color.z;
                }
            }
        }
    }
}

int main()
{
    const int width = 1000;
    const int height = 1000;

    cout << "casting rays" << endl;
    Triangle triangleOne(glm::vec3(0, 255, 0));
    Triangle triangleTwo(glm::vec3(255, 0, 0));
    Triangle triangleThree(glm::vec3(0, 0, 255));

    triangleOne.setVertices(glm::vec3(-1.5f, -1.0f, -5.0f),
                            glm::vec3(0.5f, -1.0f, -5.0f),
                            glm::vec3(-0.5f, 1.0f, -5.0f));
    triangleTwo.setVertices(glm::vec3(-1.0f, -1.0f, -5.0),
                            glm::vec3(1.0f, -1.0f, -5.0),
                            glm::vec3(0.0f, 1.0f, -5.0));
    triangleThree.setVertices(glm::vec3(-0.5f, -1.0f, -5.0f),
                              glm::vec3(1.5f, -1.0f, -5.0f),
                              glm::vec3(0.5f, 1.0f, -5.0f));

    Triangle triangles[3] = {
        triangleOne,
        triangleTwo,
        triangleThree};

    unsigned char image[width * height * 3] = {0};
    rayCast(image, width, height, triangles);

    stbi_write_bmp("output.bmp", width, height, 3, image);
    return 0;
}
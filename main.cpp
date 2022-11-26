#include <iostream>
#include "libs/glm/glm.hpp"
#include "camera.cpp"
#include "ray.cpp"
#include "triangle.cpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "libs/ImageGenerator/stb_image_write.h"

using namespace std;

Ray constructRayThroughPixel(Camera camera, int x, int y, int width, int height)
{
    float pixelNDCx = (x + 0.5) / width;
    float pixelNDCy = (y + 0.5) / height;

    float pixelScreenX = 2 * pixelNDCx - 1;
    // float pixelScreenY = 1 - 2 * pixelNDCy;
    float pixelScreenY = 2 * pixelNDCy;

    float tanA = tan(glm::radians(camera.fov * 0.5));

    float aspectRatio = width / height;
    float pixelCameraX = (2 * pixelScreenX - 1) * aspectRatio * tanA;
    float pixelCameraY = (1 - 2 * pixelScreenY) * tanA;

    glm::vec3 dir(pixelCameraX, pixelCameraY, -1);
    glm::normalize(dir);

    Ray ray(camera.origin, dir);

    return ray;
}

void rayCast(unsigned char *image, int width, int height, Camera camera, Triangle *traingles)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            const Ray ray = constructRayThroughPixel(camera, x, y, width, height);

            float tMin = INFINITY;
            for (int i = 0; i < 3; i++)
            {
                const Triangle triangle = traingles[i];

                float t;
                bool intersects = Triangle::checkIntersection(triangle, ray, t);

                if (intersects && tMin >= t)
                {
                    tMin = t;

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
    const int width = 256;
    const int height = 256;

    Triangle redTriangle;
    Triangle greenTriangle;
    Triangle blueTriangle;

    redTriangle.setColor(glm::vec3(255, 0, 0));
    greenTriangle.setColor(glm::vec3(0, 255, 0));
    blueTriangle.setColor(glm::vec3(0, 0, 255));

    redTriangle.setVertices(glm::vec3(-1.0, -0.8, -4.9),
                            glm::vec3(1, -0.8, -4.9),
                            glm::vec3(0, 1, -4.9));
    greenTriangle.setVertices(glm::vec3(-1.5, -1, -4.8),
                              glm::vec3(0.5, -1, -4.8),
                              glm::vec3(-0.5, 1, -4.8));
    blueTriangle.setVertices(glm::vec3(-2, -0.5, -4.7),
                             glm::vec3(1.7, -0.7, -5),
                             glm::vec3(0.5, 0.7, -5));

    Camera camera(glm::vec3(0, 0, 0), 50);

    Triangle triangles[3] = {
        greenTriangle,
        redTriangle,
        blueTriangle};

    unsigned char image[width * height * 3] = {0};
    rayCast(image, width, height, camera, triangles);

    stbi_write_bmp("output.bmp", width, height, 3, image);
    return 0;
}
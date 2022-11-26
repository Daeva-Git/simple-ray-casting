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
    float pixelScreenY = 1 - 2 * pixelNDCy;

    // for fov 90
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

            float t_min = INFINITY;
            for (int i = 0; i < 3; i++)
            {
                const Triangle triangle = traingles[i];

                float t;
                bool intersects = Triangle::checkIntersection(triangle, ray, t);

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
    const int width = 256;
    const int height = 256;

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

    Camera camera(glm::vec3(0, 0, 0), 90);

    Triangle triangles[3] = {
        triangleOne,
        triangleTwo,
        triangleThree};

    unsigned char image[width * height * 3] = {0};
    rayCast(image, width, height, camera, triangles);

    stbi_write_bmp("output.bmp", width, height, 3, image);
    return 0;
}
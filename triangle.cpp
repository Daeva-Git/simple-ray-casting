#include <iostream>
#include <string>
#include "libs/glm/glm.hpp"
using namespace std;

class Triangle
{
public:
    glm::vec3 color;
    glm::vec3 vertices[3];

    void setColor (glm::vec3 color) {
        this->color = color;
    }

    void setVertices(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2)
    {
        this->vertices[0] = v0;
        this->vertices[1] = v1;
        this->vertices[2] = v2;
    }

    static bool checkIntersection(Triangle triangle, Ray ray, float &t)
    {
        glm::vec3 v0 = triangle.vertices[0];
        glm::vec3 v1 = triangle.vertices[1];
        glm::vec3 v2 = triangle.vertices[2];

        glm::vec3 v0v1 = v1 - v0;
        glm::vec3 v0v2 = v2 - v0;
        glm::vec3 pvec = glm::cross(ray.dir, v0v2);
        float det = glm::dot(v0v1, pvec);

        if (det < 1e-8)
            return false;

        if (fabs(det) < 1e-8)
            return false;

        float invDet = 1 / det;

        glm::vec3 tvec = ray.orig - v0;
        float u = glm::dot(tvec, pvec) * invDet;
        if (u < 0 || u > 1)
            return false;

        glm::vec3 qvec = glm::cross(tvec, v0v1);
        float v = glm::dot(ray.dir, qvec) * invDet;
        if (v < 0 || u + v > 1)
            return false;

        t = glm::dot(v0v2, qvec) * invDet;

        return true;
    }
};

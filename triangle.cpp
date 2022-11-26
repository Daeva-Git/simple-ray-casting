#include <iostream>
#include <string>
#include "libs/glm/glm.hpp"
using namespace std;

class Triangle
{
public:
    glm::vec3 color;
    glm::vec3 vertices[3];

    Triangle(glm::vec3 color)
    {
        setUnitVertices();
        this->color = color;
    }

    void setVertices(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2)
    {
        vertices[0] = v0;
        vertices[1] = v1;
        vertices[2] = v2;
    }

    void setUnitVertices()
    {
        vertices[0] = glm::vec3(-0.5, 0.5, -1);
        vertices[1] = glm::vec3(0, -0.5, -1);
        vertices[2] = glm::vec3(0.5, 0.5, -1);
    }

    static bool checkIntersection(Triangle triangle, Ray ray, float &t, float &u, float &v)
    {
        glm::vec3 v0 = triangle.vertices[0];
        glm::vec3 v1 = triangle.vertices[1];
        glm::vec3 v2 = triangle.vertices[2];

        return checkIntersection(ray.orig, ray.dir, v0, v1, v2, t, u, v);
    }

    static bool checkIntersection(
        const glm::vec3 &orig, const glm::vec3 &dir,
        const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2,
        float &t, float &u, float &v)
    {
        glm::vec3 v0v1 = v1 - v0;
        glm::vec3 v0v2 = v2 - v0;
        glm::vec3 pvec = glm::cross(dir, v0v2);
        float det = glm::dot(v0v1, pvec);

        // if the determinant is negative the triangle is 'back facing'
        // if the determinant is close to 0, the ray misses the triangle
        if (det < 1e-8)
            return false;

        // ray and triangle are parallel if det is close to 0
        if (fabs(det) < 1e-8)
            return false;

        float invDet = 1 / det;

        glm::vec3 tvec = orig - v0;
        u = glm::dot(tvec, pvec) * invDet;
        if (u < 0 || u > 1)
            return false;

        glm::vec3 qvec = glm::cross(tvec, v0v1);
        v = glm::dot(dir, qvec) * invDet;
        if (v < 0 || u + v > 1)
            return false;

        t = glm::dot(v0v2, qvec) * invDet;

        return true;
    }
};

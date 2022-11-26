#include <string>
using namespace std;

class Triangle {
public:
    float* vertices;
    int* indices;

    Triangle()
    {
        vertices = getVertices();
        indices = getIndices();
    }

    float intersect()
    {
        return 0;
    }

    float* move() {
        for (int i = 0; i < sizeof(vertices); i++)
        {
            vertices[i] += 1;
        }
        return vertices;
    }

    float* getVertices() {
        float* vertices = new float[3 * 6];
        setPoint(vertices, 0, -0.5f, 0, 0, 0, 0, 0);
        setPoint(vertices, 1, 0.5f, 0, 0, 0, 0, 0);
        setPoint(vertices, 2, 0, 1, 0, 0, 0, 0);
        return vertices;
    }

    int* getIndices() {
        int* indices = new int[3];
        indices[0] = 0;
        indices[1] = 1;
        indices[2] = 2;
        return indices;
    }

    void setPoint(float* coordinates, int index, float x, float y, float z, float r, float g, float b) {
        index *= 6;

        // set position
        coordinates[index] = x;
        coordinates[index + 1] = y;
        coordinates[index + 2] = z;

        // color
        coordinates[index + 3] = r;
        coordinates[index + 4] = g;
        coordinates[index + 5] = b;
    }
};

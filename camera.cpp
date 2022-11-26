#include "libs/glm/glm.hpp"

class Camera {
    public:
        glm::vec3 origin;
        float fov;

        Camera (glm::vec3 origin, float fov) {
            this->origin = origin;
            this->fov = fov;
        }
};

#ifndef __PLANE__
#define __PLANE__

#include <glm/glm.hpp>

class Plane {
    public:
        Plane();
        Plane(glm::vec3, glm::vec3);

        Plane* normal(glm::vec3);
        glm::vec3 normal();

        Plane* distance(float);
        float distance();

        float getSignedDistanceToPlane(glm::vec3);

    private:
        glm::vec3 m_normal;
        float m_distance;
};

#endif
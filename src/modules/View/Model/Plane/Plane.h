#ifndef __PLANE__
#define __PLANE__

#include <glm/glm.hpp>
#include "../Model.h"

class Plane {
    public:
        Plane();
        Plane(glm::vec3, glm::vec3);

        Plane* normal(glm::vec3);
        glm::vec3 normal();

        Plane* center(glm::vec3);
        glm::vec3 center();

        Plane* materialIndex(int);
        int materialIndex();

        Plane* distance(float);
        float distance();

        float getSignedDistanceToPlane(glm::vec3);

        bool isOnForwardPlane(glm::vec3, float);

    private:
        glm::vec3 m_normal;
        glm::vec3 m_center;
        int m_materialIndex;
        float m_distance;
};

#endif
#ifndef __SPHERE__
#define __SPHERE__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Model.h"

class Sphere: public Model {
    public:
        Sphere();
        Sphere(glm::vec3, float);
        Sphere(glm::vec3, float, int);

        glm::vec3 center();
        Sphere* center(glm::vec3);

        float radius();
        Sphere* radius(float);

        int materialIndex();
        Sphere* materialIndex(int);

        Sphere* scale(glm::vec3);
        glm::vec3 scale();

    private:
        glm::vec3 m_center;
        float m_radius;
        int m_materialIndex;
};





#endif
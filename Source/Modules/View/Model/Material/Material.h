#ifndef __MATERIAL__
#define __MATERIAL__

#include <string>

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material {
    public:
        Material();

        glm::vec3 ambient();
        Material* ambient(glm::vec3);

        glm::vec3 diffuse();
        Material* diffuse(glm::vec3);

        glm::vec3 specular();
        Material* specular(glm::vec3);

        float shininess();
        Material* shininess(float);

        void printFull();

    private:
        glm::vec3 m_ambient;
        glm::vec3 m_diffuse;
        glm::vec3 m_specular;
        float m_shininess;
};



#endif
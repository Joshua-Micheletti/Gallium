#ifndef __MATERIAL__
#define __MATERIAL__

#include "glad/glad.h"
#include <string>
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
        glm::vec3 ambient_;
        glm::vec3 diffuse_;
        glm::vec3 specular_;
        float shininess_;
};



#endif
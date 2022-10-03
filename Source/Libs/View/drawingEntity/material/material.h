#ifndef __MATERIAL__
#define __MATERIAL__

#include "GLAD/glad.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material {
    public:
        Material();
        std::string shader();
        Material* shader(std::string);
        
        std::string texture();
        Material* texture(std::string);

        glm::vec3 ambient();
        Material* ambient(glm::vec3);

        glm::vec3 diffuse();
        Material* diffuse(glm::vec3);

        glm::vec3 specular();
        Material* specular(glm::vec3);

        float shininess();
        Material* shininess(float);

        void loadMaterial(std::string);

        void printFull();

    private:
        std::string shader_;
        std::string texture_;

        glm::vec3 ambient_;
        glm::vec3 diffuse_;
        glm::vec3 specular_;
        float shininess_;
};



#endif
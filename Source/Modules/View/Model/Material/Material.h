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

        glm::vec3 emissive();
        Material* emissive(glm::vec3);

        float emissivness();
        Material* emissivness(float);

        float shininess();
        Material* shininess(float);

        float reflectivness();
        Material* reflectivness(float);
    
        float albedo();
        Material* albedo(float);



        void printFull();

    private:
        glm::vec3 m_ambient;
        glm::vec3 m_diffuse;
        glm::vec3 m_specular;
        glm::vec3 m_emissive;
        float m_emissivness;
        float m_shininess;
        float m_reflectivness;
        float m_albedo;
};



#endif
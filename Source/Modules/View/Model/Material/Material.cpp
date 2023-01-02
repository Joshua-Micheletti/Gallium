#include "Material.h"


Material::Material() {
    this->m_ambient = glm::vec3(1.0f, 1.0f, 1.0f);
    this->m_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    this->m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
    this->m_shininess = 64.0f;
}


glm::vec3 Material::ambient() {
    return(this->m_ambient);
}
Material* Material::ambient(glm::vec3 a) {
    this->m_ambient = a;
    return(this);
}

glm::vec3 Material::diffuse() {
    return(this->m_diffuse);
}
Material* Material::diffuse(glm::vec3 d) {
    this->m_diffuse = d;
    return(this);
}

glm::vec3 Material::specular() {
    return(this->m_specular);
}
Material* Material::specular(glm::vec3 s) {
    this->m_specular = s;
    return(this);
}

float Material::shininess() {
    return(this->m_shininess);
}
Material* Material::shininess(float s) {
    this->m_shininess = s;
    return(this);
}


void Material::printFull() {
    // printf("\tShader: %s\n", this->shader_.c_str());
    // printf("\tTexture: %s\n", this->texture_.c_str());
}
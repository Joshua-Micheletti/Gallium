#include "Material.h"


Material::Material() {
    this->m_ambient = glm::vec3(1.0f, 1.0f, 1.0f);
    this->m_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    this->m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
    this->m_emissive = glm::vec3(0.0f, 0.0f, 0.0f);
    this->m_emissivness = 0.0f;
    this->m_shininess = 64.0f;
    this->m_reflectivness = 0.0f;
    this->m_albedo = 0.0f;
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

float Material::reflectivness() {
    return(this->m_reflectivness);
}
Material* Material::reflectivness(float r) {
    this->m_reflectivness = r;
    return(this);
}

float Material::albedo() {
    return(this->m_albedo);
}
Material* Material::albedo(float a) {
    this->m_albedo = a;
    return(this);
}

float Material::emissivness() {
    return(this->m_emissivness);
}
Material* Material::emissivness(float e) {
    this->m_emissivness = e;
    return(this);
}

glm::vec3 Material::emissive() {
    return(this->m_emissive);
}
Material* Material::emissive(glm::vec3 e) {
    this->m_emissive = e;
    return(this);
}


void Material::printFull() {
    // printf("\tShader: %s\n", this->shader_.c_str());
    // printf("\tTexture: %s\n", this->texture_.c_str());
}
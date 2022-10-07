#include "material.h"

Material::Material() {
    this->ambient_ = glm::vec3(1.0f, 1.0f, 1.0f);
    this->diffuse_ = glm::vec3(1.0f, 1.0f, 1.0f);
    this->specular_ = glm::vec3(1.0f, 1.0f, 1.0f);
    this->shininess_ = 64.0f;
}


glm::vec3 Material::ambient() {
    return(this->ambient_);
}
Material* Material::ambient(glm::vec3 a) {
    this->ambient_ = a;
    return(this);
}

glm::vec3 Material::diffuse() {
    return(this->diffuse_);
}
Material* Material::diffuse(glm::vec3 d) {
    this->diffuse_ = d;
    return(this);
}

glm::vec3 Material::specular() {
    return(this->specular_);
}
Material* Material::specular(glm::vec3 s) {
    this->specular_ = s;
    return(this);
}

float Material::shininess() {
    return(this->shininess_);
}
Material* Material::shininess(float s) {
    this->shininess_ = s;
    return(this);
}


void Material::printFull() {
    // printf("\tShader: %s\n", this->shader_.c_str());
    // printf("\tTexture: %s\n", this->texture_.c_str());
}
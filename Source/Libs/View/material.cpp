#include "material.h"

Material::Material() {
}

std::string Material::shader() {
    return(this->shader_);
}

void Material::shader(std::string name) {
    this->shader_ = name;
}

std::string Material::texture() {
    return(this->texture_);
}

void Material::texture(std::string name) {
    this->texture_ = name;
}

void Material::printFull() {
    printf("\tShader: %s\n", this->shader_.c_str());
    printf("\tTexture: %s\n", this->texture_.c_str());
}
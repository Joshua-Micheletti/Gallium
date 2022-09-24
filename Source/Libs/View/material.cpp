#include "material.h"

Material::Material() {
}

std::string Material::shader() {
    return(this->shader_);
}

void Material::shader(std::string name) {
    this->shader_ = name;
}

void Material::printFull() {
    printf("Shader: %s\n", this->shader_.c_str());
}
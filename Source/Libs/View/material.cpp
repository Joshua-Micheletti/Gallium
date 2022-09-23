#include "material.h"

Material::Material() {
    this->shader_ = Shader("test");
}

Shader Material::shader() {
    return(this->shader_);
}

void Material::printFull() {
    this->shader_.printFull();
}
#include "drawingEntity.h"

DrawingEntity::DrawingEntity() {
    this->modelMatrix_ = glm::mat4(1);
    this->translationMatrix_ = glm::mat4(1);
    this->rotationMatrix_ = glm::mat4(1);
    this->scaleMatrix_ = glm::mat4(1);
}

void DrawingEntity::model(std::string name) {
    this->model_ = name;
}

void DrawingEntity::material(std::string name) {
    this->material_ = name;
}

std::string DrawingEntity::model() {
    return(this->model_);
}

std::string DrawingEntity::material() {
    return(this->material_);
}


void DrawingEntity::translate(glm::vec3 translation) {
    this->translationMatrix_ = glm::translate(this->translationMatrix_, translation);
}

void DrawingEntity::rotate(glm::vec3 rotation) {
    this->rotationMatrix_ = glm::rotate(this->rotationMatrix_, rotation.x, glm::vec3(1, 0, 0));
    this->rotationMatrix_ = glm::rotate(this->rotationMatrix_, rotation.y, glm::vec3(0, 1, 0));
    this->rotationMatrix_ = glm::rotate(this->rotationMatrix_, rotation.z, glm::vec3(0, 0, 1));
}

void DrawingEntity::scale(glm::vec3 scale) {
    this->scaleMatrix_ = glm::scale(this->scaleMatrix_, scale);
}


// OPTIMIZE MAKING IT ONLY CALCULATE THE MODEL MATRIX WHEN THE OTHER MATRICES CHANGE
glm::mat4 DrawingEntity::modelMatrix() {
    this->modelMatrix_ = this->translationMatrix_ * this->rotationMatrix_ * this->scaleMatrix_;
    return(this->modelMatrix_);
}



void DrawingEntity::printFull() {
    printf("Model: %s\nMaterial: %s\n", this->model_.c_str(), this->material_.c_str());
}
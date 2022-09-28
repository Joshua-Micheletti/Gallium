#include "drawingEntity.h"

DrawingEntity::DrawingEntity() {
    this->modelMatrix_ = glm::mat4(1);
    this->translationMatrix_ = glm::mat4(1);
    this->rotationMatrix_ = glm::mat4(1);
    this->scaleMatrix_ = glm::mat4(1);
    this->position_ = glm::vec3(0);
}

DrawingEntity* DrawingEntity::model(std::string name) {
    this->model_ = name;
    return(this);
}

DrawingEntity* DrawingEntity::material(std::string name) {
    this->material_ = name;
    return(this);
}

std::string DrawingEntity::model() {
    return(this->model_);
}

std::string DrawingEntity::material() {
    return(this->material_);
}


DrawingEntity* DrawingEntity::translate(glm::vec3 translation) {
    this->position_ += translation;
    this->translationMatrix_ = glm::translate(this->translationMatrix_, translation);
    return(this);
}

DrawingEntity* DrawingEntity::rotate(glm::vec3 rotation) {
    this->rotationMatrix_ = glm::rotate(this->rotationMatrix_, rotation.x, glm::vec3(1, 0, 0));
    this->rotationMatrix_ = glm::rotate(this->rotationMatrix_, rotation.y, glm::vec3(0, 1, 0));
    this->rotationMatrix_ = glm::rotate(this->rotationMatrix_, rotation.z, glm::vec3(0, 0, 1));
    return(this);
}

DrawingEntity* DrawingEntity::scale(glm::vec3 scale) {
    this->scaleMatrix_ = glm::scale(this->scaleMatrix_, scale);
    return(this);
}


DrawingEntity* DrawingEntity::position(glm::vec3 position) {
    this->position_ = position;
    this->translationMatrix_ = glm::translate(glm::mat4(1), position);

    return(this);
}

glm::vec3 DrawingEntity::position() {
    return(this->position_);
}


// OPTIMIZE MAKING IT ONLY CALCULATE THE MODEL MATRIX WHEN THE OTHER MATRICES CHANGE
glm::mat4 DrawingEntity::modelMatrix() {
    this->modelMatrix_ = this->translationMatrix_ * this->rotationMatrix_ * this->scaleMatrix_;
    return(this->modelMatrix_);
}


bool DrawingEntity::isLight() {
    return(this->isLight_);
}

void DrawingEntity::isLight(bool flag) {
    this->isLight_ = flag;
}


glm::vec3 DrawingEntity::lightColor() {
    return(this->lightColor_);
}

void DrawingEntity::lightColor(glm::vec3 color) {
    this->lightColor_ = color;
}


void DrawingEntity::printFull() {
    printf("Model: %s\nMaterial: %s\n", this->model_.c_str(), this->material_.c_str());
}
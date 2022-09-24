#include "drawingEntity.h"

DrawingEntity::DrawingEntity() {

}

void DrawingEntity::setModel(std::string id) {
    this->model_ = id;
}

void DrawingEntity::setMaterial(std::string id) {
    this->material_ = id;
}

std::string DrawingEntity::model() {
    return(this->model_);
}

std::string DrawingEntity::material() {
    return(this->material_);
}

void DrawingEntity::printFull() {
    printf("Model: %s\nMaterial: %s\n", this->model_.c_str(), this->material_.c_str());
}
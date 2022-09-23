#include "drawingEntity.h"

DrawingEntity::DrawingEntity() {

}

Model* DrawingEntity::model() {
    return(&this->model_);
}

Material* DrawingEntity::material() {
    return(&this->material_);
}

void DrawingEntity::printFull() {
    this->model_.printFull();
    this->material_.printFull();
}
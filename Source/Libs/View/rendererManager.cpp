#include "rendererManager.h"

std::map<std::string, DrawingEntity*> RendererManager::drawingEntityBuffer() {
    return(this->drawingEntityBuffer_);
}

DrawingEntity* RendererManager::drawingEntity(std::string name) {
    return(this->drawingEntityBuffer_[name]);
}

std::string RendererManager::drawingEntity(std::string name, DrawingEntity* drawingEntity) {
    this->drawingEntityBuffer_[name] = drawingEntity;
    return(name);
}

void RendererManager::printFullDE(std::string name) {
    printf("Drawing Entity: %s\n", name.c_str());
    this->drawingEntityBuffer_[name]->printFull();
    printf("\n");

    std::string model = this->drawingEntityBuffer_[name]->model();

    if (model.size() != 0) {
        this->printFullM(model);
    }

    printf("\n");

    std::string material = this->drawingEntityBuffer_[name]->material();

    if (material.size() != 0) {
        this->printFullMA(material);
    }
}


std::map<std::string, Model*> RendererManager::modelBuffer() {
    return(this->modelBuffer_);
}

Model* RendererManager::model(std::string name) {
    return(this->modelBuffer_[name]);
}

std::string RendererManager::model(std::string name, Model* model) {
    this->modelBuffer_[name] = model;
    return(name);
}

void RendererManager::printFullM(std::string name) {
    printf("Model: %s\n", name.c_str());
    this->modelBuffer_[name]->print();
}


std::map<std::string, Material*> RendererManager::materialBuffer() {
    return(this->materialBuffer_);
}

Material* RendererManager::material(std::string name) {
    return(this->materialBuffer_[name]);
}

std::string RendererManager::material(std::string name, Material* material) {
    this->materialBuffer_[name] = material;
    return(name);
}

void RendererManager::printFullMA(std::string name) {
    printf("Material: %s\n", name.c_str());
    this->materialBuffer_[name]->printFull();
    printf("\n");
    std::string shader = this->materialBuffer_[name]->shader();

    if (shader.size() != 0) {
        this->printFullS(shader);
    }
}


std::map<std::string, Shader*> RendererManager::shaderBuffer() {
    return(this->shaderBuffer_);
}

Shader* RendererManager::shader(std::string name) {
    return(this->shaderBuffer_[name]);
}

std::string RendererManager::shader(std::string name, Shader* shader) {
    this->shaderBuffer_[name] = shader;
    return(name);
}

void RendererManager::printFullS(std::string name) {
    printf("Shader: %s\n", name.c_str());
    this->shaderBuffer_[name]->printFull();
}
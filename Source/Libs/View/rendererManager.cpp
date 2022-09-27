#include "rendererManager.h"

// MOVE TO UTILS.CPP
template<typename TK, typename TV>
std::vector<TV> extractValues(std::map<TK, TV> const& input_map) {
    std::vector<TV> retval;
    for (auto const& element : input_map) {
        retval.push_back(element.second);
    }
    return retval;
}
// MOVE TO UTILS.CPP
template<typename TK, typename TV>
std::vector<TK> extractKeys(std::map<TK, TV> const& input_map) {
    std::vector<TK> retval;
    for (auto const& element : input_map) {
        retval.push_back(element.first);
    }
    return retval;
}


RendererManager::RendererManager() {
    this->camera_ = new Camera(glm::vec3(30.0f, 30.0f, 30.0f),   // position
                               glm::vec3(0.0f, 225.0f, -35.0f),  // direction
                               glm::vec3(0.0f, 1.0f, 0.0f));

    this->projection_ = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 10000.0f);
}

// RETURN BUFFERS
std::map<std::string, DrawingEntity*> RendererManager::drawingEntityBuffer() {
    return(this->drawingEntityBuffer_);
}

std::map<std::string, Model*> RendererManager::modelBuffer() {
    return(this->modelBuffer_);
}

std::map<std::string, Material*> RendererManager::materialBuffer() {
    return(this->materialBuffer_);
}

std::map<std::string, Shader*> RendererManager::shaderBuffer() {
    return(this->shaderBuffer_);
}

std::map<std::string, Texture*> RendererManager::textureBuffer() {
    return(this->textureBuffer_);
}


// DRAWING ENTITY
DrawingEntity* RendererManager::drawingEntity(std::string name) {
    return(this->drawingEntityBuffer_[name]);
}

std::string RendererManager::newDrawingEntity(std::string name) {
    DrawingEntity* de = new DrawingEntity();
    this->drawingEntityBuffer_[name] = de;
    return(name);
}

std::vector<DrawingEntity*> RendererManager::drawingEntities() {
    return(extractValues(this->drawingEntityBuffer_));
}


// MODEL
Model* RendererManager::model(std::string name) {
    return(this->modelBuffer_[name]);
}

std::string RendererManager::newModel(std::string name) {
    Model* m = new Model();
    this->modelBuffer_[name] = m;
    return(name);
}

std::vector<Model*> RendererManager::models() {
    return(extractValues(this->modelBuffer_));
}

// MATERIAL
Material* RendererManager::material(std::string name) {
    return(this->materialBuffer_[name]);
}

std::string RendererManager::newMaterial(std::string name) {
    Material* ma = new Material();
    this->materialBuffer_[name] = ma;
    return(name);
}

std::vector<Material*> RendererManager::materials() {
    return(extractValues(this->materialBuffer_));
}


// SHADER
Shader* RendererManager::shader(std::string name) {
    return(this->shaderBuffer_[name]);
}

std::string RendererManager::newShader(std::string name) {
    Shader* s = new Shader();
    this->shaderBuffer_[name] = s;
    return(name);
}

std::vector<Shader*> RendererManager::shaders() {
    return(extractValues(this->shaderBuffer_));
}


// TEXTURE
Texture* RendererManager::texture(std::string name) {
    return(this->textureBuffer_[name]);
}

std::string RendererManager::newTexture(std::string name) {
    Texture* s = new Texture();
    this->textureBuffer_[name] = s;
    return(name);
}

std::vector<Texture*> RendererManager::textures() {
    return(extractValues(this->textureBuffer_));
}


Camera* RendererManager::camera() {
    return(this->camera_);
}

glm::mat4 RendererManager::projection() {
    return(this->projection_);
}

// PRINTS
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

void RendererManager::printFullM(std::string name) {
    printf("Model: %s\n", name.c_str());
    this->modelBuffer_[name]->print();
}

void RendererManager::printFullMA(std::string name) {
    printf("Material: %s\n", name.c_str());
    this->materialBuffer_[name]->printFull();
    printf("\n");
    std::string shader = this->materialBuffer_[name]->shader();
    std::string texture = this->materialBuffer_[name]->texture();

    if (shader.size() != 0) {
        this->printFullS(shader);
    }

    if (texture.size() != 0) {
        this->printFullT(texture);
    }
}

void RendererManager::printFullS(std::string name) {
    printf("Shader: %s\n", name.c_str());
    this->shaderBuffer_[name]->printFull();
}

void RendererManager::printFullT(std::string name) {
    printf("Texture: %s\n", name.c_str());
    this->textureBuffer_[name]->printFull();
}
#include "model.h"

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


// CONSTRUCTOR
Model::Model() {
    drawingMode_ = GL_TRIANGLES;

    this->modelMatrix_ = glm::mat4(1);
    this->translationMatrix_ = glm::mat4(1);
    this->rotationMatrix_ = glm::mat4(1);
    this->scaleMatrix_ = glm::mat4(1);
    this->position_ = glm::vec3(0);
    this->rotation_ = glm::vec3(0);
    this->scale_ = glm::vec3(1);

    component_t* options = new component_t;
    this->components_.push_back(options);
}

GLenum Model::drawingMode() {
    return(this->drawingMode_);
}
Model* Model::drawingMode(GLenum mode) {
    this->drawingMode_ = mode;
    return(this);
}


std::vector<component_t*> Model::components() {
    return(this->components_);
}
component_t* Model::component(int index) {
    return(this->components_[index]);
}
Model* Model::components(std::vector<component_t*> c) {
    this->components_ = c;
}

Model* Model::meshes(std::vector<std::string> m) {
    this->components_.clear();

    for (int i = 0; i < m.size(); i++) {
        component_t* options = new component_t;
        options->mesh = m[i];
        this->components_.push_back(options);
    }
}
Model* Model::mesh(std::string m) {
    this->components_[0]->mesh = m;
    return(this);
}


// Model* Model::texture(std::string t) {
//     this->components_[0]->texture_ = t;
//     return(this);
// }

Model* Model::shader(std::string s) {
    this->components_[0]->shader = s;
    return(this);
}
std::vector<std::string> Model::shaders(std::string s) {
    std::vector<std::string> shaders;
    for (int i = 0; i < this->components_.size(); i++) {
        shaders.push_back(this->components_[i]->shader);
        this->components_[i]->shader = s;
    }

    return(shaders);
}
std::vector<std::string> Model::shaders(std::vector<std::string> s) {
    std::vector<std::string> shaders;
    for (int i = 0; i < this->components_.size(); i++) {
        shaders.push_back(this->components_[i]->shader);
        this->components_[i]->shader = s[i];
    }

    return(shaders);
}

Model* Model::material(std::string m) {
    this->components_[0]->material = m;
    return(this);
}
std::string Model::material() {
    return(this->components_[0]->material);
}


Model* Model::texture(std::string t) {
    this->components_[0]->texture.general(t);
    return(this);
}
std::string Model::texture() {
    return(this->components_[0]->texture.general());
}



/*
std::string Model::texture(std::string mesh) {
    return(this->components_[mesh].texture);
}
Model* Model::texture(std::string texture, std::string mesh) {
    this->components_[mesh].texture = texture;
    return(this);
}


std::string Model::material(std::string mesh) {
    return(this->components_[mesh].material);
}
std::string Model::material() {
    return(this->components_[0].material);
}
Model* Model::material(std::string material, std::string mesh) {
    this->components_[mesh].material = material;
    return(this);
}


std::string Model::shader(std::string mesh) {
    return(this->components_[mesh].shader);
}
Model* Model::shader(std::string shader, std::string mesh) {
    this->components_[mesh].shader = shader;
    return(this);
}
*/



Model* Model::translate(glm::vec3 translation) {
    this->position_ += translation;
    this->translationMatrix_ = glm::translate(this->translationMatrix_, translation);
    return(this);
}

Model* Model::rotate(glm::vec3 rotation) {
    this->rotationMatrix_ = glm::rotate(this->rotationMatrix_, rotation.x, glm::vec3(1, 0, 0));
    this->rotationMatrix_ = glm::rotate(this->rotationMatrix_, rotation.y, glm::vec3(0, 1, 0));
    this->rotationMatrix_ = glm::rotate(this->rotationMatrix_, rotation.z, glm::vec3(0, 0, 1));
    this->rotation_ += rotation;

    return(this);
}

Model* Model::scale(glm::vec3 scale) {
    this->scaleMatrix_ = glm::scale(glm::mat4(1), scale);
    this->scale_ = scale;
    return(this);
}

// OPTIMIZE TO ONLY CALCULATE WHEN THERE'S A CHANGE
glm::mat4 Model::modelMatrix() {
    this->modelMatrix_ = this->translationMatrix_ * this->rotationMatrix_ * this->scaleMatrix_;
    return(this->modelMatrix_);
}

glm::vec3 Model::position() {
    return(this->position_);
}
Model* Model::position(glm::vec3 position) {
    this->position_ = position;
    this->translationMatrix_ = glm::translate(glm::mat4(1), position);

    return(this);
}

glm::vec3 Model::rotation() {
    return(this->rotation_);
}
Model* Model::rotation(glm::vec3 rotation) {
    this->rotation_ = rotation;
    glm::mat4 tmpRotationMatrix = glm::mat4(1);
    tmpRotationMatrix = glm::rotate(tmpRotationMatrix, rotation.x, glm::vec3(1, 0, 0));
    tmpRotationMatrix = glm::rotate(tmpRotationMatrix, rotation.y, glm::vec3(0, 1, 0));
    tmpRotationMatrix = glm::rotate(tmpRotationMatrix, rotation.z, glm::vec3(0, 0, 1));

    this->rotationMatrix_ = tmpRotationMatrix;

    return(this);
}

glm::vec3 Model::scale() {
    return(this->scale_);
}

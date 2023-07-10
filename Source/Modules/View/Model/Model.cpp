#include "Model.h"

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

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}


// CONSTRUCTOR
Model::Model() {
    m_drawingMode = GL_TRIANGLES;

    this->m_modelMatrix = glm::mat4(1);
    this->m_translationMatrix = glm::mat4(1);
    this->m_rotationMatrix = glm::mat4(1);
    this->m_scaleMatrix = glm::mat4(1);
    this->m_position = glm::vec3(0);
    this->m_rotation = glm::vec3(0);
    this->m_scale = glm::vec3(1);

    component_t* options = new component_t;
    this->m_components.push_back(options);
}

Model::~Model() {

}

GLenum Model::drawingMode() {
    return(this->m_drawingMode);
}
Model* Model::drawingMode(GLenum mode) {
    this->m_drawingMode = mode;
    return(this);
}


std::vector<component_t*> Model::components() {
    return(this->m_components);
}
component_t* Model::component(int index) {
    return(this->m_components[index]);
}
Model* Model::components(std::vector<component_t*> c) {
    this->m_components = c;
    return(this);
}

Model* Model::meshes(std::vector<std::string> m) {
    this->m_components.clear();

    for (int i = 0; i < m.size(); i++) {
        component_t* options = new component_t;
        options->mesh = m[i];
        this->m_components.push_back(options);
    }
    
    return(this);
}
Model* Model::mesh(std::string m) {
    this->m_components[0]->mesh = m;
    return(this);
}


// Model* Model::texture(std::string t) {
//     this->m_components[0]->texture_ = t;
//     return(this);
// }

Model* Model::shader(std::string s) {
    this->m_components[0]->shader = s;
    return(this);
}
std::vector<std::string> Model::shaders(std::string s) {
    std::vector<std::string> shaders;
    for (int i = 0; i < this->m_components.size(); i++) {
        shaders.push_back(this->m_components[i]->shader);
        this->m_components[i]->shader = s;
    }

    return(shaders);
}
std::vector<std::string> Model::shaders(std::vector<std::string> s) {
    std::vector<std::string> shaders;
    for (int i = 0; i < this->m_components.size(); i++) {
        shaders.push_back(this->m_components[i]->shader);
        this->m_components[i]->shader = s[i];
    }

    return(shaders);
}

Model* Model::material(std::string m) {
    this->m_components[0]->material = m;
    return(this);
}
std::string Model::material() {
    return(this->m_components[0]->material);
}


Model* Model::texture(std::string t) {
    this->m_components[0]->texture.general(t);
    return(this);
}
std::string Model::texture() {
    return(this->m_components[0]->texture.general());
}



/*
std::string Model::texture(std::string mesh) {
    return(this->m_components[mesh].texture);
}
Model* Model::texture(std::string texture, std::string mesh) {
    this->m_components[mesh].texture = texture;
    return(this);
}


std::string Model::material(std::string mesh) {
    return(this->m_components[mesh].material);
}
std::string Model::material() {
    return(this->m_components[0].material);
}
Model* Model::material(std::string material, std::string mesh) {
    this->m_components[mesh].material = material;
    return(this);
}


std::string Model::shader(std::string mesh) {
    return(this->m_components[mesh].shader);
}
Model* Model::shader(std::string shader, std::string mesh) {
    this->m_components[mesh].shader = shader;
    return(this);
}
*/



Model* Model::translate(glm::vec3 translation) {
    this->m_position += translation;
    this->m_translationMatrix = glm::translate(this->m_translationMatrix, translation);

    this->m_modelMatrix = this->m_translationMatrix * this->m_rotationMatrix * this->m_scaleMatrix;

    return(this);
}

Model* Model::rotate(glm::vec3 rotation) {
    this->m_rotationMatrix = glm::rotate(this->m_rotationMatrix, rotation.x, glm::vec3(1, 0, 0));
    this->m_rotationMatrix = glm::rotate(this->m_rotationMatrix, rotation.y, glm::vec3(0, 1, 0));
    this->m_rotationMatrix = glm::rotate(this->m_rotationMatrix, rotation.z, glm::vec3(0, 0, 1));
    this->m_rotation += rotation;

    this->m_modelMatrix = this->m_translationMatrix * this->m_rotationMatrix * this->m_scaleMatrix;

    return(this);
}

Model* Model::scale(glm::vec3 scale) {
    this->m_scaleMatrix = glm::scale(glm::mat4(1), scale);
    this->m_scale = scale;
    this->m_modelMatrix = this->m_translationMatrix * this->m_rotationMatrix * this->m_scaleMatrix;
    return(this);
}

// OPTIMIZE TO ONLY CALCULATE WHEN THERE'S A CHANGE
glm::mat4 Model::modelMatrix() {
    // this->m_modelMatrix = this->m_translationMatrix * this->m_rotationMatrix * this->m_scaleMatrix;
    return(this->m_modelMatrix);
}
Model* Model::modelMatrix(float *m) {
    this->m_modelMatrix = glm::make_mat4(m);
    this->m_modelMatrix *= this->m_scaleMatrix;
    this->m_position = glm::vec3(m[12], m[13], m[14]);
    return(this);
}

glm::vec3 Model::position() {
    return(this->m_position);
}
Model* Model::position(glm::vec3 position) {
    this->m_position = position;
    this->m_translationMatrix = glm::translate(glm::mat4(1), position);

    this->m_modelMatrix = this->m_translationMatrix * this->m_rotationMatrix * this->m_scaleMatrix;

    return(this);
}

glm::vec3 Model::rotation() {
    return(this->m_rotation);
}
Model* Model::rotation(glm::vec3 rotation) {
    this->m_rotation = rotation;
    glm::mat4 tmpRotationMatrix = glm::mat4(1);
    tmpRotationMatrix = glm::rotate(tmpRotationMatrix, rotation.x, glm::vec3(1, 0, 0));
    tmpRotationMatrix = glm::rotate(tmpRotationMatrix, rotation.y, glm::vec3(0, 1, 0));
    tmpRotationMatrix = glm::rotate(tmpRotationMatrix, rotation.z, glm::vec3(0, 0, 1));

    this->m_rotationMatrix = tmpRotationMatrix;

    return(this);
}

glm::vec3 Model::scale() {
    return(this->m_scale);
}


Model* Model::center(glm::vec3 center) {
    this->m_center = center;
    return(this);
}
glm::vec3 Model::center() {
    return(this->m_center);
}

Model* Model::radius(float radius) {
    this->m_radius = radius;
    return(this);
}
float Model::radius() {
    return(this->m_radius);
}



Model* Model::print() {
    printf("Position:\n  %sx%s: %.2f, %sy%s: %.2f, %sz%s: %.2f\n", strRed.c_str(), strNoColor.c_str(), this->m_position.x, strGreen.c_str(), strNoColor.c_str(), this->m_position.y, strBlue.c_str(), strNoColor.c_str(), this->m_position.z);
    printf("Rotation:\n  %sx%s: %.2f, %sy%s: %.2f, %sz%s: %.2f\n", strRed.c_str(), strNoColor.c_str(), this->m_rotation.x, strGreen.c_str(), strNoColor.c_str(), this->m_rotation.y, strBlue.c_str(), strNoColor.c_str(), this->m_rotation.z);
    printf("Scale:\n  %sx%s: %.2f, %sy%s: %.2f, %sz%s: %.2f\n", strRed.c_str(), strNoColor.c_str(), this->m_scale.x, strGreen.c_str(), strNoColor.c_str(), this->m_scale.y, strBlue.c_str(), strNoColor.c_str(), this->m_scale.z);

    return(this);
}

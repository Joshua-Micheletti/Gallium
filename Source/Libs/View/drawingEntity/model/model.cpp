#include "model.h"

// CONSTRUCTOR
Model::Model() {
    drawingMode_ = GL_TRIANGLES;
}

// function for loading 3D models from file to OpenGL buffers
/*
void Model::loadModel(std::string filepath) {
    this->source_ = filepath;
    // readOBJ(filepath, this->vertices_, this->uvs_, this->normals_);
    std::vector<std::vector<float>*> v;
    std::vector<std::vector<float>*> t;
    std::vector<std::vector<float>*> n;
    std::vector<std::string> m;

    // readOBJ(filepath, this->meshes_);
    readOBJ(filepath, &v, &t, &n, &m);

    // for (int i = 0; i < v.size(); i++) {
    //     printf("%d\n", v[0]->size());
    //     for (int j = 0; j < v[v.size() - 1]->size(); j++) {
    //         printf("v: %f\n", v[i][j]);
    //     }
    // }

    this->meshes_.clear();

    for (int i = 0; i < v.size(); i++) {
        std::string fullName = RM.model(this) + "_" + std::string(i);
        RM.newMesh(fullName)->vertices(*v[i])->uvs(*t[i])->normals(*n[i])->material(m[i]);
        this->meshes_.push_back(fullName);
        // this->meshes_.push_back(new Mesh());
        // this->meshes_[this->meshes_.size() - 1]->vertices(*v[i]);
        // this->meshes_[this->meshes_.size() - 1]->uvs(*t[i]);
        // this->meshes_[this->meshes_.size() - 1]->normals(*n[i]);
        // this->meshes_[this->meshes_.size() - 1]->material(m[i]);

        // this->meshes_[this->meshes_.size() - 1]->print();
    }

    
    
    // createBuffer(this->vertices_, &this->vertexBuffer_);
    // createBuffer(this->uvs_, &this->uvBuffer_);
    // createBuffer(this->normals_, &this->normalBuffer_);
}
*/


GLenum Model::drawingMode() {
    return(this->drawingMode_);
}

Model* Model::drawingMode(GLenum mode) {
    this->drawingMode_ = mode;
    return(this);
}


std::vector<std::string> Model::meshes() {
    return(this->meshes_);
}

Model* Model::meshes(std::vector<std::string> mesh) {
    this->meshes_ = mesh;
    return(this);
}


std::string Model::source() {
    return(this->source_);
}
Model* Model::source(std::string s) {
    this->source_ = s;
    return(this);
}

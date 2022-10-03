#include "mesh.h"

std::string Mesh::name() {
    return(this->name_);
}


std::vector<float> Mesh::vertices() {
    return(this->vertices_);
}

Mesh* Mesh::vertices(std::vector<float> v) {
    this->vertices_ = v;
    createBuffer(this->vertices_, &this->vertexBuffer_);
    return(this);
} 


std::vector<float> Mesh::uvs() {
    return(this->uvs_);
}

Mesh* Mesh::uvs(std::vector<float> u) {
    this->uvs_ = u;
    createBuffer(this->uvs_, &this->uvBuffer_);
    return(this);
} 


std::vector<float> Mesh::normals() {
    return(this->normals_);
}

Mesh* Mesh::normals(std::vector<float> n) {
    this->normals_ = n;
    createBuffer(this->normals_, &this->normalBuffer_);
    return(this);
} 


unsigned int Mesh::vertexBuffer() {
    return(this->vertexBuffer_);
}

unsigned int Mesh::uvBuffer() {
    return(this->uvBuffer_);
}

unsigned int Mesh::normalBuffer() {
    return(this->normalBuffer_);
}
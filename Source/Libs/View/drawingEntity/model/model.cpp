#include "model.h"

// CONSTRUCTOR
Model::Model() {
    drawingMode_ = GL_TRIANGLES;
    this->meshes_.push_back(new Mesh);
}

// function for loading 3D models from file to OpenGL buffers
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
        this->meshes_.push_back(new Mesh());
        this->meshes_[this->meshes_.size() - 1]->vertices(*v[i]);
        this->meshes_[this->meshes_.size() - 1]->uvs(*t[i]);
        this->meshes_[this->meshes_.size() - 1]->normals(*n[i]);
        this->meshes_[this->meshes_.size() - 1]->material(m[i]);

        this->meshes_[this->meshes_.size() - 1]->print();
    }

    
    
    // createBuffer(this->vertices_, &this->vertexBuffer_);
    // createBuffer(this->uvs_, &this->uvBuffer_);
    // createBuffer(this->normals_, &this->normalBuffer_);
}

// manually load the vertices into the model
void Model::loadVertices(std::vector<float> v) {
    this->vertices_ = v;
    createBuffer(this->vertices_, &this->vertexBuffer_);
}

// manually load the UVs into the model
void Model::loadUVs(std::vector<float> t) {
    this->uvs_ = t;
    createBuffer(this->uvs_, &this->uvBuffer_);
}

// manually load the normals into the model
void Model::loadNormals(std::vector<float> n) {
    this->normals_ = n;
    createBuffer(this->normals_, &this->normalBuffer_);
}


std::vector<float> Model::vertices() {
    return(this->vertices_);
}

std::vector<float> Model::UVs() {
    return(this->uvs_);
}

std::vector<float> Model::normals() {
    return(this->normals_);
}

unsigned int Model::vertexBuffer() {
    return(this->vertexBuffer_);
}

unsigned int Model::uvBuffer() {
    return(this->uvBuffer_);
}

unsigned int Model::normalBuffer() {
    return(this->normalBuffer_);
}


GLenum Model::drawingMode() {
    return(this->drawingMode_);
}

Model* Model::drawingMode(GLenum mode) {
    this->drawingMode_ = mode;
    return(this);
}


std::vector<Mesh*> Model::meshes() {
    return(this->meshes_);
}

Model* Model::meshes(std::vector<Mesh*> mesh) {
    this->meshes_ = mesh;
    return(this);
}


void Model::printVertices() {
    int length = maxLength(this->vertices_);

    printf("\nVertices:\n");
    for (int i = 0; i < this->vertices_.size(); i++) {
        std::string vertexValue = std::to_string(this->vertices_[i]);
        for (int j = vertexValue.size(); j < length; j++) {
            vertexValue.insert(0, 1, ' ');
        }

        if (i % 9 == 0) {
            printf("Face %d:\n", (int)(i / 9));
        }
        if (i % 3 == 2) {
            printf("\033[0;34mZ\033[0m = %s\n", vertexValue.c_str());
        } else {
            printf("%s = %s ", i % 3 == 0 ? "\033[0;31mX\033[0m" : "\033[0;32mY\033[0m", vertexValue.c_str());
        }

        if (i % 9 == 8) {
            printf("\n");
        }
    }
}

void Model::printUVs() {
    int length = maxLength(this->uvs_);

    printf("\nUVs: \n");
    for (int i = 0; i < this->uvs_.size(); i++) {
        std::string uvValue = std::to_string(this->uvs_[i]);
        for (int j = uvValue.size(); j < length; j++) {
            uvValue.insert(0, 1, ' ');
        }

        if (i % 6 == 0) {
            printf("Face %d:\n", (int)(i / 6));
        }
        if (i % 2 == 1) {
            printf("\033[0;32mV\033[0m = %s\n", uvValue.c_str());
        } else {
            printf("\033[0;31mU\033[0m = %s ", uvValue.c_str());
        }

        if (i % 6 == 5) {
            printf("\n");
        }
    }
}

void Model::printNormals() {
    int length = maxLength(this->normals_);

    printf("\nNormals: \n");
    for (int i = 0; i < this->normals_.size(); i++) {
        std::string normalValue = std::to_string(this->normals_[i]);
        for (int j = normalValue.size(); j < length; j++) {
            normalValue.insert(0, 1, ' ');
        }
        if (i % 9 == 0) {
            printf("Face %d:\n", (int)(i / 9));
        }
        if (i % 3 == 2) {
            printf("\033[0;34mZ\033[0m = %s\n", normalValue.c_str());
        } else {
            printf("%s = %s ", i % 3 == 0 ? "\033[0;31mX\033[0m" : "\033[0;32mY\033[0m", normalValue.c_str());
        }

        if (i % 9 == 8) {
            printf("\n");
        }
    }
}

void Model::printFull() {
    this->printVertices();
    this->printUVs();
    this->printNormals();
    this->print();
}

void Model::printFace(int face) {
    if (face < 0 || face > countFaces(this->vertices_)) {
        printf("%sInvalid face, model has %d faces%s\n", strRed.c_str(), countFaces(this->vertices_), strNoColor.c_str());
        return;
    }

    int vLength = maxLength(this->vertices_);
    int uLength = maxLength(this->uvs_);
    int nLength = maxLength(this->normals_);

    int length = vLength > uLength ? vLength : uLength;
    length = nLength > length ? nLength : length;

    printf("Face %d:\n", face);
    printf("Vertices: \n");
    for (int i = face * 9; i < (face + 1) * 9; i++) {
        std::string value = std::to_string(this->vertices_[i]);
        for (int j = value.size(); j < length; j++) {
            value.insert(0, 1, ' ');
        }
        if (i % 3 == 2) {
            printf("%sZ%s = %s\n", strBlue.c_str(), strNoColor.c_str(), value.c_str());
        } else {
            printf("%s%c%s = %s ", i % 3 == 0 ? strRed.c_str() : strGreen.c_str(), i % 3 == 0 ? 'X' : 'Y', strNoColor.c_str(), value.c_str());
        }
    }

    printf("\nUVs: \n");
    for (int i = face * 6; i < (face + 1) * 6; i++) {
        std::string value = std::to_string(this->uvs_[i]);
        for (int j = value.size(); j < length; j++) {
            value.insert(0, 1, ' ');
        }
        if (i % 2 == 1) {
            printf("%sV%s = %s\n", strGreen.c_str(), strNoColor.c_str(), value.c_str());
        } else {
            printf("%sU%s = %s ", strRed.c_str(), strNoColor.c_str(), value.c_str());
        }
    }

    printf("\nNormals:\n");
    for (int i = face * 9; i < (face + 1) * 9; i++) {
        std::string value = std::to_string(this->normals_[i]);
        for (int j = value.size(); j < length; j++) {
            value.insert(0, 1, ' ');
        }
        if (i % 3 == 2) {
            printf("%sZ%s = %s\n", strBlue.c_str(), strNoColor.c_str(), value.c_str());
        } else {
            printf("%s%c%s = %s ", i % 3 == 0 ? strRed.c_str() : strGreen.c_str(), i % 3 == 0 ? 'X' : 'Y', strNoColor.c_str(), value.c_str());
        }
    }
}

void Model::print() {
    printf("Source = %s\nVertices = %d\nUVs = %d\nNormals = %d\nFaces = %d\n",
            this->source_.c_str(),
            (int)(this->vertices_.size() / 3),
            (int)(this->uvs_.size() / 2),
            (int)(this->normals_.size() / 3),
            (int)(this->vertices_.size() / 9));
}



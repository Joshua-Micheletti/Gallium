#include "mesh.h"

Mesh::Mesh() {
    this->material_ = "MA_Default";
}


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


std::string Mesh::material() {
    return(this->material_);
}

Mesh* Mesh::material(std::string ma) {
    this->material_ = ma;
    return(this);
}



void Mesh::printVertices() {
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

void Mesh::printUVs() {
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

void Mesh::printNormals() {
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

void Mesh::printFull() {
    this->printVertices();
    this->printUVs();
    this->printNormals();
    this->print();
}

void Mesh::printFace(int face) {
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

void Mesh::print() {
    printf("Source = %s\nVertices = %d\nUVs = %d\nNormals = %d\nFaces = %d\nMaterial = %s\n",
            "this->source_.c_str()",
            (int)(this->vertices_.size() / 3),
            (int)(this->uvs_.size() / 2),
            (int)(this->normals_.size() / 3),
            (int)(this->vertices_.size() / 9),
            this->material_.c_str());
}
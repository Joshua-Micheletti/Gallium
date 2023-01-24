#include "Mesh.h"

Mesh::Mesh() {
    this->m_expectedMaterial = "MA_Default";
}


std::string Mesh::name() {
    return(this->m_name);
}


std::vector<float> Mesh::vertices() {
    return(this->m_vertices);
}
Mesh* Mesh::vertices(std::vector<float> v) {
    this->m_vertices = v;
    createBuffer(this->m_vertices, &this->m_vertexBuffer);
    return(this);
} 


std::vector<float> Mesh::uvs() {
    return(this->m_uvs);
}
Mesh* Mesh::uvs(std::vector<float> u) {
    this->m_uvs = u;
    createBuffer(this->m_uvs, &this->m_uvBuffer);
    return(this);
} 


std::vector<float> Mesh::normals() {
    return(this->m_normals);
}
Mesh* Mesh::normals(std::vector<float> n) {
    this->m_normals = n;
    createBuffer(this->m_normals, &this->m_normalBuffer);
    return(this);
} 


std::vector<unsigned int> Mesh::indices() {
    return(this->m_indices);
}
Mesh* Mesh::indices(std::vector<unsigned int> i) {
    this->m_indices = i;
    createIndexBuffer(this->m_indices, &this->m_indexBuffer);
    return(this);
}


unsigned int Mesh::vertexBuffer() {
    return(this->m_vertexBuffer);
}

unsigned int Mesh::uvBuffer() {
    return(this->m_uvBuffer);
}

unsigned int Mesh::normalBuffer() {
    return(this->m_normalBuffer);
}

unsigned int Mesh::indexBuffer() {
    return(this->m_indexBuffer);
}


Mesh* Mesh::expectedMaterial(std::string ma) {
    this->m_expectedMaterial = ma;
    return(this);
}
std::string Mesh::expectedMaterial() {
    return(this->m_expectedMaterial);
}



void Mesh::printVertices() {
    int length = maxLength(this->m_vertices);
    
    printf("\nVertices:\n");
    for (int i = 0; i < this->m_vertices.size(); i++) {
        std::string vertexValue = std::to_string(this->m_vertices[i]);
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
    int length = maxLength(this->m_uvs);

    printf("\nUVs: \n");
    for (int i = 0; i < this->m_uvs.size(); i++) {
        std::string uvValue = std::to_string(this->m_uvs[i]);
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
    int length = maxLength(this->m_normals);

    printf("\nNormals: \n");
    for (int i = 0; i < this->m_normals.size(); i++) {
        std::string normalValue = std::to_string(this->m_normals[i]);
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
    if (face < 0 || face > countFaces(this->m_vertices)) {
        printf("%sInvalid face, model has %d faces%s\n", strRed.c_str(), countFaces(this->m_vertices), strNoColor.c_str());
        return;
    }

    int vLength = maxLength(this->m_vertices);
    int uLength = maxLength(this->m_uvs);
    int nLength = maxLength(this->m_normals);

    int length = vLength > uLength ? vLength : uLength;
    length = nLength > length ? nLength : length;

    printf("Face %d:\n", face);
    printf("Vertices: \n");
    for (int i = face * 9; i < (face + 1) * 9; i++) {
        std::string value = std::to_string(this->m_vertices[i]);
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
        std::string value = std::to_string(this->m_uvs[i]);
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
        std::string value = std::to_string(this->m_normals[i]);
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
    printf("Source = %s\nVertices = %d\nUVs = %d\nNormals = %d\nFaces = %d\n",
            "this->source_.c_str()",
            (int)(this->m_vertices.size() / 3),
            (int)(this->m_uvs.size() / 2),
            (int)(this->m_normals.size() / 3),
            (int)(this->m_vertices.size() / 9));
}
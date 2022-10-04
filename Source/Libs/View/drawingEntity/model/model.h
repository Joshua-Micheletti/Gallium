#ifndef __MODEL__
#define __MODEL__

#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../../utils.h"
#include "mesh/mesh.h"

class Model {
    public:
        Model();
        void loadModel(std::string);

        void loadVertices(std::vector<float>);
        void loadUVs(std::vector<float>);
        void loadNormals(std::vector<float>);

        std::vector<float> vertices();
        std::vector<float> UVs();
        std::vector<float> normals();

        unsigned int vertexBuffer();
        unsigned int uvBuffer();
        unsigned int normalBuffer();

        GLenum drawingMode();
        Model* drawingMode(GLenum);

        std::vector<Mesh*> meshes();
        Model* meshes(std::vector<Mesh*>);

        void printVertices();
        void printUVs();
        void printNormals();
        void printFull();
        void print();
        void printFace(int);

    private:
        std::string source_;
        std::vector<float> vertices_;
        std::vector<float> uvs_;
        std::vector<float> normals_;

        std::vector<Mesh*> meshes_;

        unsigned int vertexBuffer_;
        unsigned int uvBuffer_;
        unsigned int normalBuffer_;

        GLenum drawingMode_;
};

#endif
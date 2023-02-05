#ifndef __MESH__
#define __MESH__

#include <string>
#include <vector>

#include "../../../Utils/utils.h"
#include "../../../Utils/vboindexer.hpp"

class Mesh {
    public:
        Mesh();

        std::string name();

        Mesh* vertices(std::vector<float>);
        std::vector<float> vertices();
        Mesh* uvs(std::vector<float>);
        std::vector<float> uvs();
        Mesh* normals(std::vector<float>);
        std::vector<float> normals();
        Mesh* indices(std::vector<unsigned int>);
        Mesh* indices(std::vector<float>, std::vector<float>, std::vector<float>);
        std::vector<unsigned int> indices();

        glm::vec3 center();
        Mesh* center(glm::vec3);
        float radius();
        Mesh* radius(float);

        glm::vec3 max();
        Mesh* max(glm::vec3);
        glm::vec3 min();
        Mesh* min(glm::vec3);

        unsigned int vertexBuffer();
        unsigned int uvBuffer();
        unsigned int normalBuffer();
        unsigned int indexBuffer();

        Mesh* expectedMaterial(std::string);
        std::string expectedMaterial();

        void printVertices();
        void printUVs();
        void printNormals();
        void printFull();
        void print();
        void printFace(int);

    private:
        std::string m_name;

        std::string m_expectedMaterial;

        std::vector<float> m_vertices;
        std::vector<float> m_uvs;
        std::vector<float> m_normals;
        std::vector<unsigned int> m_indices;

        float m_radius;
        glm::vec3 m_center;
        glm::vec3 m_max;
        glm::vec3 m_min;

        unsigned int m_vertexBuffer;
        unsigned int m_uvBuffer;
        unsigned int m_normalBuffer;
        unsigned int m_indexBuffer;
};

#endif
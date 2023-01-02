#ifndef __MESH__
#define __MESH__

#include <string>
#include <vector>

#include "../../../utils.h"

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

        unsigned int vertexBuffer();
        unsigned int uvBuffer();
        unsigned int normalBuffer();

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

        unsigned int m_vertexBuffer;
        unsigned int m_uvBuffer;
        unsigned int m_normalBuffer;
};

#endif
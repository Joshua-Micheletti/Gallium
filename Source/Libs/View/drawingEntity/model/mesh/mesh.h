#ifndef __MESH__
#define __MESH__

#include <string>
#include <vector>
#include "../../../../utils.h"

class Mesh {
    public:
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

    private:
        std::string name_;

        std::vector<float> vertices_;
        std::vector<float> uvs_;
        std::vector<float> normals_;

        unsigned int vertexBuffer_;
        unsigned int uvBuffer_;
        unsigned int normalBuffer_;
};

#endif
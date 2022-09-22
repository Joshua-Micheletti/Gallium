#ifndef __MODEL__
#define __MODEL__

#include <string>
#include <vector>
#include "../utils.h"

class Model {
    public:
        Model();
        void loadModel(std::string);
        std::vector<float> getVertices();
        std::vector<float> getUVs();
        std::vector<float> getNormals();
        void printVertices();
        void printUVs();
        void printNormals();
        void printFull();
        void print();
        void printFace(int);

    private:
        std::string source;
        std::vector<float> vertices;
        std::vector<float> uvs;
        std::vector<float> normals;
};

#endif
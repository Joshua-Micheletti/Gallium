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

        GLenum drawingMode();
        Model* drawingMode(GLenum);

        std::vector<std::string> meshes();
        Model* meshes(std::vector<std::string>);

        std::string source();
        Model* source(std::string);

    private:
        std::string source_;

        std::vector<std::string> meshes_;

        GLenum drawingMode_;
};

#endif
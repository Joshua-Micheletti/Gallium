#ifndef __DRAWINGENTITY__
#define __DRAWINGENTITY__

//#include "../global.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <iostream>

class DrawingEntity {
    public:
        DrawingEntity();
        std::string model();
        std::string material();

        void model(std::string);
        void material(std::string);

        glm::mat4 modelMatrix();
        glm::mat4 translationMatrix();
        glm::mat4 rotationMatrix();
        glm::mat4 scaleMatrix();

        void translate(glm::vec3);
        void rotate(glm::vec3);
        void scale(glm::vec3);

        void printFull();

    private:
        std::string model_;
        std::string material_;

        glm::mat4 modelMatrix_;
        glm::mat4 translationMatrix_;
        glm::mat4 rotationMatrix_;
        glm::mat4 scaleMatrix_;
};

#endif
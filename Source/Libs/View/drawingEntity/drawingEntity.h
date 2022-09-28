#ifndef __DRAWINGENTITY__
#define __DRAWINGENTITY__

//#include "../global.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLAD/glad.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <iostream>

class DrawingEntity {
    public:
        DrawingEntity();
        std::string model();
        std::string material();

        DrawingEntity* model(std::string);
        DrawingEntity* material(std::string);

        glm::mat4 modelMatrix();
        glm::mat4 translationMatrix();
        glm::mat4 rotationMatrix();
        glm::mat4 scaleMatrix();

        DrawingEntity* translate(glm::vec3);
        DrawingEntity* rotate(glm::vec3);
        DrawingEntity* scale(glm::vec3);

        glm::vec3 position();
        DrawingEntity* position(glm::vec3);

        glm::vec3 lightColor();
        void lightColor(glm::vec3);

        bool isLight();
        void isLight(bool);

        void printFull();

    private:
        std::string model_;
        std::string material_;

        glm::mat4 modelMatrix_;
        glm::mat4 translationMatrix_;
        glm::mat4 rotationMatrix_;
        glm::mat4 scaleMatrix_;

        glm::vec3 position_;

        // FIND A WAY TO TURN LIGHT INTO A SUBCLASS
        bool isLight_;
        glm::vec3 lightColor_;
};

#endif
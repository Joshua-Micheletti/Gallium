#ifndef __RENDERERMANAGER__
#define __RENDERERMANAGER__

#include <map>
#include <string>
#include "drawingEntity.h"
#include "model.h"
#include "material.h"
#include "shader.h"

class RendererManager {
    public:
        std::map<std::string, DrawingEntity*> drawingEntityBuffer();
        DrawingEntity* drawingEntity(std::string);
        std::string drawingEntity(std::string, DrawingEntity*);
        void printFullDE(std::string);

        std::map<std::string, Model*> modelBuffer();
        Model* model(std::string);
        std::string model(std::string, Model*);
        void printFullM(std::string);

        std::map<std::string, Material*> materialBuffer();
        Material* material(std::string);
        std::string material(std::string, Material*);
        void printFullMA(std::string);

        std::map<std::string, Shader*> shaderBuffer();
        Shader* shader(std::string);
        std::string shader(std::string, Shader*);
        void printFullS(std::string);

    private:
        std::map<std::string, DrawingEntity*> drawingEntityBuffer_;
        std::map<std::string, Model*> modelBuffer_;
        std::map<std::string, Material*> materialBuffer_;
        std::map<std::string, Shader*> shaderBuffer_;
};

#endif
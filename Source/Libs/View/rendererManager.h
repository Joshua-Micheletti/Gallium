#ifndef __RENDERERMANAGER__
#define __RENDERERMANAGER__

#include <map>
#include <string>
#include "drawingEntity.h"
#include "model.h"
#include "material.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>

class RendererManager {
    public:
        RendererManager();

        std::map<std::string, DrawingEntity*> drawingEntityBuffer();
        std::map<std::string, Model*> modelBuffer();
        std::map<std::string, Material*> materialBuffer();
        std::map<std::string, Shader*> shaderBuffer();
        std::map<std::string, Texture*> textureBuffer();

        std::vector<DrawingEntity*> drawingEntities();
        std::vector<Model*> models();
        std::vector<Material*> materials();
        std::vector<Shader*> shaders();
        std::vector<Texture*> textures();

        std::vector<std::string> modelNames();

        DrawingEntity* drawingEntity(std::string);
        Model* model(std::string);
        Material* material(std::string);
        Shader* shader(std::string);
        Texture* texture(std::string);

        DrawingEntity* newDrawingEntity(std::string);
        Model* newModel(std::string);
        Material* newMaterial(std::string);
        Shader* newShader(std::string);
        Texture* newTexture(std::string);

        void printFullDE(std::string);
        void printFullM(std::string);
        void printFullMA(std::string);    
        void printFullS(std::string);
        void printFullT(std::string);

        Camera* camera();
        glm::mat4 projection();

        std::string skybox();
        void skybox(std::string);

    private:
        std::map<std::string, DrawingEntity*> drawingEntityBuffer_;
        std::map<std::string, Model*> modelBuffer_;
        std::map<std::string, Material*> materialBuffer_;
        std::map<std::string, Shader*> shaderBuffer_;
        std::map<std::string, Texture*> textureBuffer_;

        Camera* camera_;
        glm::mat4 projection_;
        std::string skybox_;
};

#endif
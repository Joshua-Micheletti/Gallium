#ifndef __RENDERERMANAGER__
#define __RENDERERMANAGER__

#include <map>
#include <string>
#include "../drawingEntity/drawingEntity.h"
#include "../drawingEntity/model/model.h"
#include "../drawingEntity/material/material.h"
#include "../drawingEntity/material/shader/shader.h"
#include "../drawingEntity/material/texture/texture.h"
#include "../camera/camera.h"
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
        std::map<std::string, Mesh*> meshBuffer();

        std::vector<DrawingEntity*> drawingEntities();
        std::vector<Model*> models();
        std::vector<Material*> materials();
        std::vector<Shader*> shaders();
        std::vector<Texture*> textures();
        std::vector<Mesh*> meshes();

        std::vector<std::string> drawingEntityNames();
        std::vector<std::string> modelNames();
        std::vector<std::string> materialNames();
        std::vector<std::string> shaderNames();
        std::vector<std::string> textureNames();
        std::vector<std::string> meshNames();

        DrawingEntity* drawingEntity(std::string);
        Model* model(std::string);
        Material* material(std::string);
        Shader* shader(std::string);
        Texture* texture(std::string);
        Mesh* mesh(std::string);

        DrawingEntity* newDrawingEntity(std::string);
        Model* newModel(std::string);
        Material* newMaterial(std::string);
        Shader* newShader(std::string);
        Texture* newTexture(std::string);
        Mesh* newMesh(std::string);

        std::string drawingEntity(DrawingEntity*);
        std::string model(Model*);
        std::string material(Material*);
        std::string shader(Shader*);
        std::string texture(Texture*);
        std::string mesh(Mesh*);

        int samples();
        RendererManager* samples(int);

        bool depth();
        RendererManager* depth(bool);

        void printFullDE(std::string);
        void printFullM(std::string);
        void printFullMA(std::string);    
        void printFullS(std::string);
        void printFullT(std::string);

        Camera* camera();
        glm::mat4 projection();
        void projection(glm::mat4);

        std::string skybox();
        void skybox(std::string);

        std::string mainLight();
        void mainLight(std::string);

        std::string selectedEntity();
        void selectedEntity(std::string);

        std::string outlineShader();
        void outlineShader(std::string);

        std::string highlightShader();
        void highlightShader(std::string);

        std::vector<std::string> loadMTL(std::string);
        void loadModel(std::string);
        void loadModel(std::string, std::string);


        void material(std::string, std::string);
        void applyMaterials(std::vector<std::string>, std::vector<std::string>);

    private:
        std::map<std::string, DrawingEntity*> drawingEntityBuffer_;
        std::map<std::string, Model*> modelBuffer_;
        std::map<std::string, Material*> materialBuffer_;
        std::map<std::string, Shader*> shaderBuffer_;
        std::map<std::string, Texture*> textureBuffer_;
        std::map<std::string, Mesh*> meshBuffer_;

        Camera* camera_;
        glm::mat4 projection_;
        std::string skybox_;
        std::string mainLight_;
        std::string selectedEntity_;
        std::string outlineShader_;
        std::string highlightShader_;

        int samples_;
        bool depth_;
};

#endif
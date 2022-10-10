#ifndef __RENDERERMANAGER__
#define __RENDERERMANAGER__

#include <map>
#include <string>
#include "../model/model.h"
#include "../model/material/material.h"
#include "../model/shader/shader.h"
#include "../model/texture/texture.h"
#include "../camera/camera.h"
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
#include "../../utils.h"

class RendererManager {
    public:
        // CONSTRUCTOR
        RendererManager();

        // getters for the various maps
        std::map<std::string, Model*> modelBuffer();
        std::map<std::string, Material*> materialBuffer();
        std::map<std::string, Shader*> shaderBuffer();
        std::map<std::string, Texture*> textureBuffer();
        std::map<std::string, Mesh*> meshBuffer();

        // getters for the various lists
        std::vector<Model*> models();
        std::vector<Material*> materials();
        std::vector<Shader*> shaders();
        std::vector<Texture*> textures();
        std::vector<Mesh*> meshes();

        // getters for the various lists of names
        std::vector<std::string> modelNames();
        std::vector<std::string> materialNames();
        std::vector<std::string> shaderNames();
        std::vector<std::string> textureNames();
        std::vector<std::string> meshNames();

        // getters for singular elements
        Model* model(std::string);
        Material* material(std::string);
        Shader* shader(std::string);
        Texture* texture(std::string);
        Mesh* mesh(std::string);

        // methods for creating new elements
        Model* newModel(std::string);
        Material* newMaterial(std::string);
        Shader* newShader(std::string);
        Texture* newTexture(std::string);
        Mesh* newMesh(std::string);
        // method for creating a new mesh loaded from an obj file
        Mesh* newMesh(std::string, std::string);

        // getters for element names starting from the object itself
        std::string model(Model*);
        std::string material(Material*);
        std::string shader(Shader*);
        std::string texture(Texture*);
        std::string mesh(Mesh*);

        int samples();
        RendererManager* samples(int);

        bool depth();
        RendererManager* depth(bool);

        void printFullM(std::string);
        void printFullMA(std::string);    
        void printFullS(std::string);
        void printFullT(std::string);

        Camera* camera();
        RendererManager* camera(std::string);

        glm::mat4 projection();
        RendererManager* projection(std::string);
        void setProjection(std::string, glm::mat4);

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

        std::string whiteShader();
        void whiteShader(std::string);

        std::vector<std::string> loadMTL(std::string);
        void loadModel(std::string);
        std::string loadModel(std::string, std::string);


        void material(std::string, std::string);
        void applyMaterials(std::vector<std::string>, std::vector<std::string>);

    private:
        std::map<std::string, Model*> modelBuffer_;
        std::map<std::string, Material*> materialBuffer_;
        std::map<std::string, Shader*> shaderBuffer_;
        std::map<std::string, Texture*> textureBuffer_;
        std::map<std::string, Mesh*> meshBuffer_;

        std::map<std::string, Camera*> cameras_;
        std::map<std::string, glm::mat4> projections_;

        std::string currentCamera_;
        std::string currentProjection_;

        std::string skybox_;
        std::string mainLight_;
        std::string selectedEntity_;
        std::string outlineShader_;
        std::string highlightShader_;
        std::string whiteShader_;

        int samples_;
        bool depth_;
};

#endif
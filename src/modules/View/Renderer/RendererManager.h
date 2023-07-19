#ifndef __RENDERERMANAGER__
#define __RENDERERMANAGER__

#include <map>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>

#include "../../Utils/utils.h"
#include "../../Utils/vboindexer.hpp"
#include "../../Utils/Timer.h"
#include "../../Utils/Debugger.h"

#include "../Model/Model.h"
#include "../Model/Material/Material.h"
#include "../Model/Shader/Shader.h"
#include "../Model/Texture/Texture.h"
#include "../Model/Sphere/Sphere.hpp"
#include "../Model/Plane/Plane.h"
#include "../Camera/Camera.hpp"

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
        
        std::vector<float> spheres();
        std::vector<float> planes();
        // std::vector<float> materials();


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

        std::vector<float> materialValues();

        std::vector<glm::mat4> modelMats();

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

        Sphere* newSphere(std::string, glm::vec3, float);
        Plane* newPlane(std::string, glm::vec3, glm::vec3);

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
        Camera* getCamera(std::string);

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

        std::string defaultModel();
        RendererManager* defaultModel(std::string);

        std::string defaultTexture();
        RendererManager* defaultTexture(std::string);

        std::string defaultShader();
        RendererManager* defaultShader(std::string);

        std::string defaultMesh();
        RendererManager* defaultMesh(std::string);

        std::string defaultMaterial();
        RendererManager* defaultMaterial(std::string);

        std::vector<std::string> loadMTL(std::string);
        void loadModel(std::string);
        std::string loadModel(std::string, std::string);

        void calculateBoundingSphere(std::string);

        void material(std::string, std::string);
        void applyMaterials(std::vector<std::string>, std::vector<std::string>);

        bool debug();
        void debug(bool);

        bool accumulate();
        RendererManager* accumulate(bool);

        bool denoise();
        RendererManager* denoise(bool);

        void updated();
        bool pathTrace();
        RendererManager* pathTrace(bool);

    private:
        std::map<std::string, Model*> m_modelBuffer;
        std::map<std::string, Material*> m_materialBuffer;
        std::map<std::string, Shader*> m_shaderBuffer;
        std::map<std::string, Texture*> m_textureBuffer;
        std::map<std::string, Mesh*> m_meshBuffer;

        // std::map<std::string, Sphere*> m_spheres;
        std::map<std::string, Plane*> m_planes;

        std::map<std::string, Camera*> m_cameras;

        std::string m_currentCamera;
        std::string m_currentProjection;

        std::string m_skybox;
        std::string m_mainLight;
        std::string m_selectedEntity;
        std::string m_outlineShader;
        std::string m_highlightShader;
        std::string m_whiteShader;

        std::string m_defaultModel;
        std::string m_defaultMaterial;
        std::string m_defaultShader;
        std::string m_defaultMesh;
        std::string m_defaultTexture;

        std::string m_boundingSphere;

        int m_samples;
        bool m_accumulate;
        bool m_denoise;
        bool m_depth;
        bool m_toUpdate;

        std::string m_primitiveBox;
        std::string m_primitiveSphere;
        std::string m_primitiveQuad;

        bool m_debug;
        bool m_pathTrace;

        void setupVariables();
        void setupDefaults();
        void setupRenderingObjects();
};

#endif
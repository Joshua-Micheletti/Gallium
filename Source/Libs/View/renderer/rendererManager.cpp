#include "rendererManager.h"

// MOVE TO UTILS.CPP
template<typename TK, typename TV>
std::vector<TV> extractValues(std::map<TK, TV> const& input_map) {
    std::vector<TV> retval;
    for (auto const& element : input_map) {
        retval.push_back(element.second);
    }
    return retval;
}
// MOVE TO UTILS.CPP
template<typename TK, typename TV>
std::vector<TK> extractKeys(std::map<TK, TV> const& input_map) {
    std::vector<TK> retval;
    for (auto const& element : input_map) {
        retval.push_back(element.first);
    }
    return retval;
}

void createAxis(Mesh* axis) {
	std::vector<float> axisColor;
	axisColor.push_back(1.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(1.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(1.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(1.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(1.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(1.0f);

	axis->uvs(axisColor);

	std::vector<float> axisVertices;
	axisVertices.push_back(100.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(-100.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(100.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(-100.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(100.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(-100.0f);

	axis->vertices(axisVertices);
}

// CONSTRUCTOR
RendererManager::RendererManager() {
    // SETUP CAMERAS
    // initialize the default camera
    this->cameras_["default"] = new Camera(glm::vec3(30.0f, 30.0f, 30.0f),   // position
                                           glm::vec3(0.0f, 225.0f, -35.0f),  // direction
                                           glm::vec3(0.0f, 1.0f, 0.0f));     // up
    // initialize the reflection camera
    this->cameras_["reflection"] = new Camera(glm::vec3(0.0f, 0.0f, 0.0f),   // position
                                              glm::vec3(0.0f, 0.0f, 0.0f),   // direction
                                              glm::vec3(0.0f, -1.0f, 0.0f)); // up
    // set the current camera to the default one
    this->currentCamera_ = "default";

    // SETUP PROJECTIONS
    // initialize the default projection
    this->projections_["default"] = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 10000.0f);
    // intialize the reflection projection
    this->projections_["reflection"] = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10000.0f);
    // set the current projection to the default one
    this->currentProjection_ = "default";

    // SETUP RENDER
    // initialize the samples for multisampling
    this->samples_ = 16;
    // disable the depth buffer view
    this->depth_ = false;

    // SETUP DEFAULTS
    // these values will be used when the called component is not found or when a model is initialized
    this->defaultMesh_ = "ME_Default";
    this->defaultTexture_ = "T_Default";
    this->defaultShader_ = "S_Default";
    this->defaultModel_ = "M_Default";
    this->defaultMaterial_ = "MA_Default";
    // load the respective default components
    this->newMesh(this->defaultMesh_, "../Models/Default/box2.obj");
    this->newShader(this->defaultShader_)->loadShader("../Shader/default/default.vert", "../Shader/default/default.frag");
    this->newTexture(this->defaultTexture_)->loadTexture("../Textures/Default/default2.jpg");
    this->newMaterial(this->defaultMaterial_);

    // SETUP GLOBAL ENTITIES
    // shader for rendering a model's outline when selected
    this->outlineShader_ = "S_Outline";
    // shader for rendering a model's geometry through other models when selected
    this->highlightShader_ = "S_Highlight";
    // shader for rendering white objects (used for stencil mask and for light)
    this->whiteShader_ = "S_White";
    // main light model
    this->mainLight_ = "M_Light";
    // skybox model
    this->skybox_ = "M_Skybox";

    // load the built-in shaders
    this->newShader("S_White")->loadShader("../Shader/white/white.vert", "../Shader/white/white.frag");
    this->newShader("S_Highlight")->loadShader("../Shader/highlight/highlight.vert", "../Shader/highlight/highlight.frag");
    this->newShader("S_Outline")->loadShader("../Shader/outline/outline.vert", "../Shader/outline/outline.frag");
    
    // SETUP SKYBOX
    // load the skybox shader
    this->newShader("S_Skybox")->loadShader("../Shader/skybox/skybox.vert", "../Shader/skybox/skybox.frag");
    // load a cubemap with the textures coming from the skybox location
    std::vector<std::string> faces;
	std::string directory = "Epic_BlueSunset";
    std::string location = "../Textures/Default/";
	faces.push_back(location + directory + "/right.png"); //right
	faces.push_back(location + directory + "/left.png");  //left
	faces.push_back(location + directory + "/top.png");   //top
	faces.push_back(location + directory + "/bottom.png");//bottom
	faces.push_back(location + directory + "/front.png"); //front
	faces.push_back(location + directory + "/back.png");  //back
    this->newTexture("T_Skybox")->loadCubemap(faces);
    // create the skybox model
    this->newModel("M_Skybox")->shader("S_Skybox")->texture("T_Skybox");

    // SETUP AXIS
    // create a new axis model
    this->newModel("M_Axis");
    createAxis(this->newMesh("ME_Axis"));
    // load the shader to render the axis
    this->newShader("S_Color")->loadShader("../Shader/color/color.vert", "../Shader/color/color.frag");
    // RENDERING THE AXIS WITH LINES IS REALLY SLOW FOR SOME REASON
    this->model("M_Axis")->mesh("ME_Axis")->shader("S_Color")->drawingMode(GL_LINES);

    // SETUP LIGHT
    // create a new light model
    this->newModel("M_Light");
    // load the sphere model
    this->newMesh("ME_Sphere", "../Models/Default/sphere7.obj");
    // create a material for the light (this will interact with every light calculation)
    this->newMaterial("MA_Light");
    this->model("M_Light")->mesh("ME_Sphere")->material("MA_Light")->shader("S_White");
    
    // initialize the selected entity (none)
    this->selectedEntity_ = "";

    printf("setup the renderer manager\n");
}


void RendererManager::skybox(std::string name) {
    this->skybox_ = name;
}
std::string RendererManager::skybox() {
    return(this->skybox_);
}


void RendererManager::mainLight(std::string name) {
    this->mainLight_ = name;
}
std::string RendererManager::mainLight() {
    return(this->mainLight_);
}


void RendererManager::selectedEntity(std::string name) {
    this->selectedEntity_ = name;
}
std::string RendererManager::selectedEntity() {
    return(this->selectedEntity_);
}


void RendererManager::outlineShader(std::string name) {
    this->outlineShader_ = name;
}
std::string RendererManager::outlineShader() {
    return(this->outlineShader_);
}


void RendererManager::highlightShader(std::string name) {
    this->highlightShader_ = name;
}
std::string RendererManager::highlightShader() {
    return(this->highlightShader_);
}


void RendererManager::whiteShader(std::string name) {
    this->whiteShader_ = name;
}
std::string RendererManager::whiteShader() {
    return(this->whiteShader_);
}


// RETURN BUFFERS
std::map<std::string, Model*> RendererManager::modelBuffer() {
    return(this->modelBuffer_);
}
std::map<std::string, Material*> RendererManager::materialBuffer() {
    return(this->materialBuffer_);
}
std::map<std::string, Shader*> RendererManager::shaderBuffer() {
    return(this->shaderBuffer_);
}
std::map<std::string, Texture*> RendererManager::textureBuffer() {
    return(this->textureBuffer_);
}
std::map<std::string, Mesh*> RendererManager::meshBuffer() {
    return(this->meshBuffer_);
}


// MODEL
Model* RendererManager::model(std::string name) {
    if (this->modelBuffer_.find(name) != this->modelBuffer_.end()) {
        return(this->modelBuffer_[name]);
    } else {
        return(this->modelBuffer_[this->defaultModel_]);
    }
}
std::string RendererManager::model(Model *m) {
    for (auto it = this->modelBuffer_.begin(); it != this->modelBuffer_.end(); it++) {
        if (it->second == m) {
            return(it->first);
        }
    }

    return("");
}
Model* RendererManager::newModel(std::string name) {
    Model* m = new Model();
    this->modelBuffer_[name] = m;
    return(this->modelBuffer_[name]);
}
std::vector<Model*> RendererManager::models() {
    return(extractValues(this->modelBuffer_));
}
std::vector<std::string> RendererManager::modelNames() {
    return(extractKeys(this->modelBuffer_));
}


// MATERIAL
Material* RendererManager::material(std::string name) {
    if (this->materialBuffer_.count(name) == 0) {
        return(this->materialBuffer_[this->defaultMaterial_]);
    } else {
        return(this->materialBuffer_[name]);
    }
}
std::string RendererManager::material(Material *ma) {
    for (auto it = this->materialBuffer_.begin(); it != this->materialBuffer_.end(); it++) {
        if (it->second == ma) {
            return(it->first);
        }
    }

    return("");
}
Material* RendererManager::newMaterial(std::string name) {
    Material* ma = new Material();
    this->materialBuffer_[name] = ma;
    return(this->materialBuffer_[name]);
}
std::vector<Material*> RendererManager::materials() {
    return(extractValues(this->materialBuffer_));
}
std::vector<std::string> RendererManager::materialNames() {
    return(extractKeys(this->materialBuffer_));
}


// SHADER
Shader* RendererManager::shader(std::string name) {
    if (this->shaderBuffer_.count(name) == 0) {
        return(this->shaderBuffer_[this->defaultShader_]);
    } else {
        return(this->shaderBuffer_[name]);
    }
    
}
std::string RendererManager::shader(Shader *s) {
    for (auto it = this->shaderBuffer_.begin(); it != this->shaderBuffer_.end(); it++) {
        if (it->second == s) {
            return(it->first);
        }
    }

    return("");
}
Shader* RendererManager::newShader(std::string name) {
    Shader* s = new Shader();
    this->shaderBuffer_[name] = s;
    return(this->shaderBuffer_[name]);
}
std::vector<Shader*> RendererManager::shaders() {
    return(extractValues(this->shaderBuffer_));
}
std::vector<std::string> RendererManager::shaderNames() {
    return(extractKeys(this->shaderBuffer_));
}


// TEXTURE
Texture* RendererManager::texture(std::string name) {
    if (this->textureBuffer_.count(name) == 0) {
        return(this->textureBuffer_[this->defaultTexture_]);
    } else {
        return(this->textureBuffer_[name]);
    }
    
}
std::string RendererManager::texture(Texture *t) {
    for (auto it = this->textureBuffer_.begin(); it != this->textureBuffer_.end(); it++) {
        if (it->second == t) {
            return(it->first);
        }
    }

    return("");
}
Texture* RendererManager::newTexture(std::string name) {
    Texture* s = new Texture();
    this->textureBuffer_[name] = s;
    return(this->textureBuffer_[name]);
}
std::vector<Texture*> RendererManager::textures() {
    return(extractValues(this->textureBuffer_));
}
std::vector<std::string> RendererManager::textureNames() {
    return(extractKeys(this->textureBuffer_));
}


// MESH
Mesh* RendererManager::mesh(std::string name) {
    if (this->meshBuffer_.count(name) == 0) {
        return(this->meshBuffer_[this->defaultMesh_]);
    } else {
        return(this->meshBuffer_[name]);
    }    
}
std::string RendererManager::mesh(Mesh *t) {
    for (auto it = this->meshBuffer_.begin(); it != this->meshBuffer_.end(); it++) {
        if (it->second == t) {
            return(it->first);
        }
    }

    return("");
}
Mesh* RendererManager::newMesh(std::string name) {
    Mesh* m = new Mesh();
    this->meshBuffer_[name] = m;
    return(this->meshBuffer_[name]);
}
Mesh* RendererManager::newMesh(std::string name, std::string filepath) {
    std::vector<float> v;
    std::vector<float> t;
    std::vector<float> n;

    if (readOBJMesh(filepath, &v, &t, &n)) {
        this->newMesh(name)->vertices(v)->uvs(t)->normals(n);
        return(this->meshBuffer_[name]);
    } else {
        return(NULL);
    }
}
std::vector<Mesh*> RendererManager::meshes() {
    return(extractValues(this->meshBuffer_));
}
std::vector<std::string> RendererManager::meshNames() {
    return(extractKeys(this->meshBuffer_));
}


Camera* RendererManager::camera() {
    return(this->cameras_[this->currentCamera_]);
}
RendererManager* RendererManager::camera(std::string s) {
    this->currentCamera_ = s;
    return(this);
}


glm::mat4 RendererManager::projection() {
    return(this->projections_[this->currentProjection_]);
}
RendererManager* RendererManager::projection(std::string p) {
    this->currentProjection_ = p;
}

void RendererManager::setProjection(std::string name, glm::mat4 m) {
    this->projections_[name] = m;
}


int RendererManager::samples() {
    return(this->samples_);
}
RendererManager* RendererManager::samples(int s) {
    this->samples_ = s;
}

bool RendererManager::depth() {
    return(this->depth_);
}
RendererManager* RendererManager::depth(bool d) {
    this->depth_ = d;
}

std::string RendererManager::defaultModel() {
    return(this->defaultModel_);
}
RendererManager* RendererManager::defaultModel(std::string s) {
    if (this->modelBuffer_.count(s) != 0) {
        this->defaultModel_ = s;
    }

    return(this);
}

std::string RendererManager::defaultMaterial() {
    return(this->defaultMaterial_);
}
RendererManager* RendererManager::defaultMaterial(std::string s) {
    if (this->materialBuffer_.count(s) != 0) {
        this->defaultMaterial_ = s;
    }

    return(this);
}

std::string RendererManager::defaultTexture() {
    return(this->defaultTexture_);
}
RendererManager* RendererManager::defaultTexture(std::string s) {
    if (this->textureBuffer_.count(s) != 0) {
        this->defaultTexture_ = s;
    }

    return(this);
}

std::string RendererManager::defaultShader() {
    return(this->defaultShader_);
}
RendererManager* RendererManager::defaultShader(std::string s) {
    if (this->shaderBuffer_.count(s) != 0) {
        this->defaultShader_ = s;
    }

    return(this);
}

std::string RendererManager::defaultMesh() {
    return(this->defaultMesh_);
}
RendererManager* RendererManager::defaultMesh(std::string s) {
    if (this->meshBuffer_.count(s) != 0) {
        this->defaultMesh_ = s;
    }

    return(this);
}



std::vector<std::string> RendererManager::loadMTL(std::string filepath) {
    std::vector<std::string> names;
    std::vector<std::vector<float>*> ambient;
    std::vector<std::vector<float>*> diffuse;
    std::vector<std::vector<float>*> specular;
    std::vector<float> shininess;

    readMTL(filepath, &names, &ambient, &diffuse, &specular, &shininess);

    for (int i = 0; i < names.size(); i++) {
        this->newMaterial(names[i])->ambient(glm::vec3((*ambient[i])[0], (*ambient[i])[1], (*ambient[i])[2]))->
                                     diffuse(glm::vec3((*diffuse[i])[0], (*diffuse[i])[1], (*diffuse[i])[2]))->
                                     specular(glm::vec3((*specular[i])[0], (*specular[i])[1], (*specular[i])[2]))->
                                     shininess(shininess[i]);
    }

    return(names);
}

void RendererManager::loadModel(std::string filepath) {
    std::vector<std::vector<float>*> v;
    std::vector<std::vector<float>*> t;
    std::vector<std::vector<float>*> n;
    std::vector<std::string> m;

    readOBJ(filepath, &v, &t, &n, &m);

    std::vector<std::string> meshes;

    for (int i = 0; i < v.size(); i++) {
        std::string fullName = filepath + "_" + std::to_string(i);
        this->newMesh(fullName)->vertices(*v[i])->uvs(*t[i])->normals(*n[i]);
        
        if (m.size() != 0) {
            this->mesh(fullName)->expectedMaterial(m[i]);
        }

        meshes.push_back(fullName);
    }

    this->newModel(filepath)->meshes(meshes);
}


std::string RendererManager::loadModel(std::string filepath, std::string name) {
    std::vector<std::vector<float>*> v;
    std::vector<std::vector<float>*> t;
    std::vector<std::vector<float>*> n;
    std::vector<std::string> m;

    readOBJ(filepath, &v, &t, &n, &m);

    std::vector<std::string> meshes;
    std::vector<component_t*> components;

    for (int i = 0; i < v.size(); i++) {
        std::string fullName = name + "_" + std::to_string(i);
        this->newMesh(fullName)->vertices(*v[i])->uvs(*t[i])->normals(*n[i]);

        component_t* tmp = new component_t;

        if (m.size() != 0) {
            this->mesh(fullName)->expectedMaterial(m[i]);
            if (find(m[i], this->materialNames()) != -1) {
                tmp->material = m[i];
            }
        }

        meshes.push_back(fullName);
        tmp->mesh = fullName;
        components.push_back(tmp);
    }

    this->newModel(name)->components(components);

    return(name);
}


// PRINTS
/*
void RendererManager::printFullM(std::string name) {
    printf("Model: %s\n", name.c_str());
    // this->modelBuffer_[name]->print();
}
void RendererManager::printFullMA(std::string name) {
    printf("Material: %s\n", name.c_str());
    this->materialBuffer_[name]->printFull();
    printf("\n");
    std::string shader = this->materialBuffer_[name]->shader();
    std::string texture = this->materialBuffer_[name]->texture();

    if (shader.size() != 0) {
        this->printFullS(shader);
    }

    if (texture.size() != 0) {
        this->printFullT(texture);
    }
}
void RendererManager::printFullS(std::string name) {
    printf("Shader: %s\n", name.c_str());
    this->shaderBuffer_[name]->printFull();
}
void RendererManager::printFullT(std::string name) {
    printf("Texture: %s\n", name.c_str());
    this->textureBuffer_[name]->printFull();
}
*/

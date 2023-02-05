#include "RendererManager.h"

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
    Timer RMSetupTimer;

    debugger.printRM("DEBUGGING RENDERER MANAGER");

    // SETUP CAMERAS
    // initialize the default camera
    this->m_cameras["default"] = new Camera(glm::vec3(30.0f, 30.0f, 30.0f),   // position
                                           glm::vec3(0.0f, 225.0f, -65.0f),  // direction
                                           glm::vec3(0.0f, 1.0f, 0.0f));     // up
    // initialize the reflection camera
    this->m_cameras["reflection"] = new Camera(glm::vec3(0.0f, 0.0f, 0.0f),   // position
                                              glm::vec3(0.0f, 0.0f, 0.0f),   // direction
                                              glm::vec3(0.0f, -1.0f, 0.0f)); // up
    // set the current camera to the default one
    this->m_currentCamera = "default";

    debugger.printRM("SETUP CAMERAS");

    // SETUP PROJECTIONS
    // initialize the default projection
    this->m_projections["default"] = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 10000.0f);
    // intialize the reflection projection
    this->m_projections["reflection"] = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10000.0f);
    // set the current projection to the default one
    this->m_currentProjection = "default";

    debugger.printRM("SETUP PROJECTIONS");

    // SETUP RENDER
    // initialize the samples for multisampling
    this->m_samples = 1;
    // disable the depth buffer view
    this->m_depth = false;

    debugger.printRM("SETUP VARIABLES");

    // SETUP DEFAULTS
    // these values will be used when the called component is not found or when a model is initialized
    this->m_defaultMesh = "ME_Default";
    this->m_defaultTexture = "T_Default";
    this->m_defaultShader = "S_Default";
    this->m_defaultModel = "M_Default";
    this->m_defaultMaterial = "MA_Default";

    debugger.printRM("SETUP DEFAULT COMPONENT NAMES");

    // load the respective default components
    this->newMesh(this->m_defaultMesh, "../Models/Default/box2.obj");

    this->newShader(this->m_defaultShader)->loadShader("../Shader/default/default.vert", "../Shader/default/default.frag");
    this->newTexture(this->m_defaultTexture)->loadTexture("../Textures/Default/default2.jpg");
    this->newMaterial(this->m_defaultMaterial);

    debugger.printRM("LOADED DEFAULT COMPONENTS");

    // SETUP GLOBAL ENTITIES
    // shader for rendering a model's outline when selected
    this->m_outlineShader = "S_Outline";
    // shader for rendering a model's geometry through other models when selected
    this->m_highlightShader = "S_Highlight";
    // shader for rendering white objects (used for stencil mask and for light)
    this->m_whiteShader = "S_White";
    // main light model
    this->m_mainLight = "M_Light";
    // skybox model
    this->m_skybox = "M_Skybox";

    debugger.printRM("SETUP GLOBAL ENTITIES");

    // load the built-in shaders
    this->newShader("S_White")->loadShader("../Shader/white/white.vert", "../Shader/white/white.frag");
    this->newShader("S_Highlight")->loadShader("../Shader/highlight/highlight.vert", "../Shader/highlight/highlight.frag");
    this->newShader("S_Outline")->loadShader("../Shader/outline/outline.vert", "../Shader/outline/outline.frag");
    
    debugger.printRM("LOADED NECESSARY SHADERS");

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
    
    debugger.printRM("LOADED SKYBOX CUBEMAP");

    // create the skybox model
    this->newModel("M_Skybox")->shader("S_Skybox")->texture("T_Skybox");

    debugger.printRM("SETUP SKYBOX");

    // SETUP AXIS
    // create a new axis model
    this->newModel("M_Axis");
    createAxis(this->newMesh("ME_Axis"));
    // load the shader to render the axis
    this->newShader("S_Color")->loadShader("../Shader/color/color.vert", "../Shader/color/color.frag");
    // RENDERING THE AXIS WITH LINES IS REALLY SLOW FOR SOME REASON
    this->model("M_Axis")->mesh("ME_Axis")->shader("S_Color")->drawingMode(GL_LINES);

    debugger.printRM("SETUP AXIS");

    // SETUP LIGHT
    // create a new light model
    this->newModel("M_Light");
    // load the sphere model
    this->newMesh("ME_Sphere", "../Models/Default/sphere7.obj");
    // create a material for the light (this will interact with every light calculation)
    this->newMaterial("MA_Light");
    this->model("M_Light")->mesh("ME_Sphere")->material("MA_Light")->shader("S_White");

    debugger.printRM("SETUP LIGHT ENTITY");

    // this->newMesh("ME_BoundingSphere", "../Models/Default/boundingSphere.obj");
    // this->model("M_BoundingSphere")->mesh("ME_BoundingSphere");
    
    // initialize the selected entity (none)
    this->m_selectedEntity = "";

    printf("\n%sSetup the renderer manager%s\n", strGreen.c_str(), strNoColor.c_str());
    RMSetupTimer.print();
}


void RendererManager::skybox(std::string name) {
    this->m_skybox = name;
}
std::string RendererManager::skybox() {
    return(this->m_skybox);
}


void RendererManager::mainLight(std::string name) {
    this->m_mainLight = name;
}
std::string RendererManager::mainLight() {
    return(this->m_mainLight);
}


void RendererManager::selectedEntity(std::string name) {
    this->m_selectedEntity = name;
}
std::string RendererManager::selectedEntity() {
    return(this->m_selectedEntity);
}


void RendererManager::outlineShader(std::string name) {
    this->m_outlineShader = name;
}
std::string RendererManager::outlineShader() {
    return(this->m_outlineShader);
}


void RendererManager::highlightShader(std::string name) {
    this->m_highlightShader = name;
}
std::string RendererManager::highlightShader() {
    return(this->m_highlightShader);
}


void RendererManager::whiteShader(std::string name) {
    this->m_whiteShader = name;
}
std::string RendererManager::whiteShader() {
    return(this->m_whiteShader);
}


// RETURN BUFFERS
std::map<std::string, Model*> RendererManager::modelBuffer() {
    return(this->m_modelBuffer);
}
std::map<std::string, Material*> RendererManager::materialBuffer() {
    return(this->m_materialBuffer);
}
std::map<std::string, Shader*> RendererManager::shaderBuffer() {
    return(this->m_shaderBuffer);
}
std::map<std::string, Texture*> RendererManager::textureBuffer() {
    return(this->m_textureBuffer);
}
std::map<std::string, Mesh*> RendererManager::meshBuffer() {
    return(this->m_meshBuffer);
}


// MODEL
Model* RendererManager::model(std::string name) {
    if (this->m_modelBuffer.find(name) != this->m_modelBuffer.end()) {
        return(this->m_modelBuffer[name]);
    } else {
        return(this->m_modelBuffer[this->m_defaultModel]);
    }
}
std::string RendererManager::model(Model *m) {
    for (auto it = this->m_modelBuffer.begin(); it != this->m_modelBuffer.end(); it++) {
        if (it->second == m) {
            return(it->first);
        }
    }

    return("");
}
Model* RendererManager::newModel(std::string name) {
    Model* m = new Model();
    this->m_modelBuffer[name] = m;
    this->calculateBoundingSphere(name);
    return(this->m_modelBuffer[name]);
}
std::vector<Model*> RendererManager::models() {
    return(extractValues(this->m_modelBuffer));
}
std::vector<std::string> RendererManager::modelNames() {
    return(extractKeys(this->m_modelBuffer));
}


// MATERIAL
Material* RendererManager::material(std::string name) {
    if (this->m_materialBuffer.count(name) == 0) {
        return(this->m_materialBuffer[this->m_defaultMaterial]);
    } else {
        return(this->m_materialBuffer[name]);
    }
}
std::string RendererManager::material(Material *ma) {
    for (auto it = this->m_materialBuffer.begin(); it != this->m_materialBuffer.end(); it++) {
        if (it->second == ma) {
            return(it->first);
        }
    }

    return("");
}
Material* RendererManager::newMaterial(std::string name) {
    Material* ma = new Material();
    this->m_materialBuffer[name] = ma;
    return(this->m_materialBuffer[name]);
}
std::vector<Material*> RendererManager::materials() {
    return(extractValues(this->m_materialBuffer));
}
std::vector<std::string> RendererManager::materialNames() {
    return(extractKeys(this->m_materialBuffer));
}


// SHADER
Shader* RendererManager::shader(std::string name) {
    if (this->m_shaderBuffer.count(name) == 0) {
        return(this->m_shaderBuffer[this->m_defaultShader]);
    } else {
        return(this->m_shaderBuffer[name]);
    }
    
}
std::string RendererManager::shader(Shader *s) {
    for (auto it = this->m_shaderBuffer.begin(); it != this->m_shaderBuffer.end(); it++) {
        if (it->second == s) {
            return(it->first);
        }
    }

    return("");
}
Shader* RendererManager::newShader(std::string name) {
    Shader* s = new Shader();
    this->m_shaderBuffer[name] = s;
    return(this->m_shaderBuffer[name]);
}
std::vector<Shader*> RendererManager::shaders() {
    return(extractValues(this->m_shaderBuffer));
}
std::vector<std::string> RendererManager::shaderNames() {
    return(extractKeys(this->m_shaderBuffer));
}


// TEXTURE
Texture* RendererManager::texture(std::string name) {
    if (this->m_textureBuffer.count(name) == 0) {
        return(this->m_textureBuffer[this->m_defaultTexture]);
    } else {
        return(this->m_textureBuffer[name]);
    }
}
std::string RendererManager::texture(Texture *t) {
    for (auto it = this->m_textureBuffer.begin(); it != this->m_textureBuffer.end(); it++) {
        if (it->second == t) {
            return(it->first);
        }
    }

    return("");
}
Texture* RendererManager::newTexture(std::string name) {
    Texture* s = new Texture();
    this->m_textureBuffer[name] = s;
    return(this->m_textureBuffer[name]);
}
std::vector<Texture*> RendererManager::textures() {
    return(extractValues(this->m_textureBuffer));
}
std::vector<std::string> RendererManager::textureNames() {
    return(extractKeys(this->m_textureBuffer));
}


// MESH
Mesh* RendererManager::mesh(std::string name) {
    if (this->m_meshBuffer.count(name) == 0) {
        return(this->m_meshBuffer[this->m_defaultMesh]);
    } else {
        return(this->m_meshBuffer[name]);
    }    
}
std::string RendererManager::mesh(Mesh *t) {
    for (auto it = this->m_meshBuffer.begin(); it != this->m_meshBuffer.end(); it++) {
        if (it->second == t) {
            return(it->first);
        }
    }

    return("");
}
Mesh* RendererManager::newMesh(std::string name) {
    Mesh* m = new Mesh();
    this->m_meshBuffer[name] = m;
    return(this->m_meshBuffer[name]);
}
Mesh* RendererManager::newMesh(std::string name, std::string filepath) {
    std::vector<float> v;
    std::vector<float> t;
    std::vector<float> n;

    if (readOBJMesh(filepath, &v, &t, &n)) {
        this->newMesh(name)->indices(v, t, n);
        return(this->m_meshBuffer[name]);
    } else {
        return(NULL);
    }
}
std::vector<Mesh*> RendererManager::meshes() {
    return(extractValues(this->m_meshBuffer));
}
std::vector<std::string> RendererManager::meshNames() {
    return(extractKeys(this->m_meshBuffer));
}


Camera* RendererManager::camera() {
    return(this->m_cameras[this->m_currentCamera]);
}
RendererManager* RendererManager::camera(std::string s) {
    this->m_currentCamera = s;
    return(this);
}


glm::mat4 RendererManager::projection() {
    return(this->m_projections[this->m_currentProjection]);
}
RendererManager* RendererManager::projection(std::string p) {
    this->m_currentProjection = p;
    return(this);
}

void RendererManager::setProjection(std::string name, glm::mat4 m) {
    this->m_projections[name] = m;
}


int RendererManager::samples() {
    return(this->m_samples);
}
RendererManager* RendererManager::samples(int s) {
    this->m_samples = s;
    return(this);
}

bool RendererManager::depth() {
    return(this->m_depth);
}
RendererManager* RendererManager::depth(bool d) {
    this->m_depth = d;
    return(this);
}

std::string RendererManager::defaultModel() {
    return(this->m_defaultModel);
}
RendererManager* RendererManager::defaultModel(std::string s) {
    if (this->m_modelBuffer.count(s) != 0) {
        this->m_defaultModel = s;
    }

    return(this);
}

std::string RendererManager::defaultMaterial() {
    return(this->m_defaultMaterial);
}
RendererManager* RendererManager::defaultMaterial(std::string s) {
    if (this->m_materialBuffer.count(s) != 0) {
        this->m_defaultMaterial = s;
    }

    return(this);
}

std::string RendererManager::defaultTexture() {
    return(this->m_defaultTexture);
}
RendererManager* RendererManager::defaultTexture(std::string s) {
    if (this->m_textureBuffer.count(s) != 0) {
        this->m_defaultTexture = s;
    }

    return(this);
}

std::string RendererManager::defaultShader() {
    return(this->m_defaultShader);
}
RendererManager* RendererManager::defaultShader(std::string s) {
    if (this->m_shaderBuffer.count(s) != 0) {
        this->m_defaultShader = s;
    }

    return(this);
}

std::string RendererManager::defaultMesh() {
    return(this->m_defaultMesh);
}
RendererManager* RendererManager::defaultMesh(std::string s) {
    if (this->m_meshBuffer.count(s) != 0) {
        this->m_defaultMesh = s;
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
        this->newMesh(fullName)->indices(*v[i], *t[i], *n[i]);
        
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
        this->newMesh(fullName)->indices(*v[i], *t[i], *n[i]);

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

    this->calculateBoundingSphere(name);

    return(name);
}


void RendererManager::calculateBoundingSphere(std::string model) {
    glm::vec3 center = glm::vec3(0);
    float radius = 0.0f;

    // for (int i = 0; i < this->model(model)->components().size(); i++) {
    //     center += this->mesh(this->model(model)->components()[i]->mesh)->center();
    // }

    // center.x /= this->model(model)->components().size();
    // center.y /= this->model(model)->components().size();
    // center.z /= this->model(model)->components().size();

    int vertices = 0;

    for (int i = 0; i < this->model(model)->components().size(); i++) {
        for (int j = 0; j < this->mesh(this->model(model)->components()[i]->mesh)->vertices().size(); j += 3) {
            center.x += this->mesh(this->model(model)->components()[i]->mesh)->vertices()[j];
            center.y += this->mesh(this->model(model)->components()[i]->mesh)->vertices()[j + 1];
            center.z += this->mesh(this->model(model)->components()[i]->mesh)->vertices()[j + 2];
            vertices++;
        }
    }

    center.x /= vertices;
    center.y /= vertices;
    center.z /= vertices;

    printf("%s: %lf, %lf, %lf\n", model.c_str(), center.x, center.y, center.z);

    float distance;

    for (int i = 0; i < this->model(model)->components().size(); i++) {
        for (int j = 0; j < this->mesh(this->model(model)->components()[i]->mesh)->vertices().size(); j += 3) {
            distance = sqrt(pow(center.x - this->mesh(this->model(model)->components()[i]->mesh)->vertices()[j], 2) + pow(center.y - this->mesh(this->model(model)->components()[i]->mesh)->vertices()[j + 1], 2) + pow(center.z - this->mesh(this->model(model)->components()[i]->mesh)->vertices()[j + 2], 2));
            if (distance > radius) {
                radius = distance;
            }
        }
    }

    printf("%s: %lf\n", model.c_str(), radius);

    this->model(model)->center(center)->radius(radius);
}

// PRINTS
/*
void RendererManager::printFullM(std::string name) {
    printf("Model: %s\n", name.c_str());
    // this->m_modelBuffer[name]->print();
}
void RendererManager::printFullMA(std::string name) {
    printf("Material: %s\n", name.c_str());
    this->m_materialBuffer[name]->printFull();
    printf("\n");
    std::string shader = this->m_materialBuffer[name]->shader();
    std::string texture = this->m_materialBuffer[name]->texture();

    if (shader.size() != 0) {
        this->printFullS(shader);
    }

    if (texture.size() != 0) {
        this->printFullT(texture);
    }
}
void RendererManager::printFullS(std::string name) {
    printf("Shader: %s\n", name.c_str());
    this->m_shaderBuffer[name]->printFull();
}
void RendererManager::printFullT(std::string name) {
    printf("Texture: %s\n", name.c_str());
    this->m_textureBuffer[name]->printFull();
}
*/

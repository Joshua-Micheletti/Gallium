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


RendererManager::RendererManager() {
    this->camera_ = new Camera(glm::vec3(30.0f, 30.0f, 30.0f),   // position
                               glm::vec3(0.0f, 225.0f, -35.0f),  // direction
                               glm::vec3(0.0f, 1.0f, 0.0f));

    this->projection_ = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 10000.0f);

    this->samples_ = 16;
    this->depth_ = false;

    this->newShader("S_Default")->loadShader("../Shader/lighting/lighting.vert", "../Shader/lighting/lighting.frag");
    this->newTexture("T_Default")->loadTexture("../Textures/default2.jpg");
    this->newMaterial("MA_Default")->shader("S_Default")->texture("T_Default");
    this->newModel("M_Default")->loadModel("../Models/box2.obj");

    this->newShader("S_Skybox")->loadShader("../Shader/skybox/skybox.vert", "../Shader/skybox/skybox.frag");
    std::vector<std::string> faces;
	std::string directory = "Epic_BlueSunset";
	faces.push_back("../Textures/Skybox/" + directory + "/right.png"); //right
	faces.push_back("../Textures/Skybox/" + directory + "/left.png");  //left
	faces.push_back("../Textures/Skybox/" + directory + "/top.png");   //top
	faces.push_back("../Textures/Skybox/" + directory + "/bottom.png");//bottom
	faces.push_back("../Textures/Skybox/" + directory + "/front.png"); //front
	faces.push_back("../Textures/Skybox/" + directory + "/back.png");  //back
    this->newTexture("T_Skybox")->loadCubemap(faces);
    this->newMaterial("MA_Skybox")->shader("S_Skybox")->texture("T_Skybox");
    this->newDrawingEntity("DE_Skybox")->model("M_Default")->material("MA_Skybox");
    this->skybox_ = "DE_Skybox";

    createAxis(this->newModel("M_Axis")->drawingMode(GL_LINES)->meshes()[0]);
    this->newShader("S_Axis")->loadShader("../Shader/color/color.vert", "../Shader/color/color.frag");
    this->newMaterial("MA_Axis")->shader("S_Axis");
    // this->newDrawingEntity("DE_Axis")->model("M_Axis")->material("MA_Axis");

    this->newModel("M_Light")->loadModel("../Models/sphere7.obj");
    this->model("M_Light")->meshes()[0]->material("MA_Default");
	this->newShader("S_Light")->loadShader("../Shader/white/white.vert", "../Shader/white/white.frag");
	this->newMaterial("MA_Light")->shader("S_Light");
	this->newDrawingEntity("DE_Light")->model("M_Light")->material("MA_Light")->isLight(true)->lightColor(glm::vec3(1));
    this->mainLight_ = "DE_Light";

    this->newShader("S_Highlight")->loadShader("../Shader/highlight/highlight.vert", "../Shader/highlight/highlight.frag");
    this->newShader("S_Outline")->loadShader("../Shader/outline/outline.vert", "../Shader/outline/outline.frag");

    this->outlineShader_ = "S_Outline";
    this->highlightShader_ = "S_Highlight";

    this->selectedEntity_ = "";
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

// RETURN BUFFERS
std::map<std::string, DrawingEntity*> RendererManager::drawingEntityBuffer() {
    return(this->drawingEntityBuffer_);
}

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


// DRAWING ENTITY
DrawingEntity* RendererManager::drawingEntity(std::string name) {
    if (this->drawingEntityBuffer_.find(name) != this->drawingEntityBuffer_.end()) {
        return(this->drawingEntityBuffer_[name]);
    } else {
        return(NULL);
    }
}

std::string RendererManager::drawingEntity(DrawingEntity *d) {
    for (auto it = this->drawingEntityBuffer_.begin(); it != this->drawingEntityBuffer_.end(); it++) {
        if (it->second == d) {
            return(it->first);
        }
    }

    return("");
}

DrawingEntity* RendererManager::newDrawingEntity(std::string name) {
    DrawingEntity* de = new DrawingEntity();

    de->model("M_Default")->material("MA_Default");

    this->drawingEntityBuffer_[name] = de;
    return(this->drawingEntityBuffer_[name]);
}

std::vector<DrawingEntity*> RendererManager::drawingEntities() {
    // DrawingEntity* tmpSkybox = this->drawingEntityBuffer_[this->skybox_];
    // this->drawingEntityBuffer_.erase(this->skybox_);
    return(extractValues(this->drawingEntityBuffer_));
    // this->drawingEntityBuffer_[this->skybox_] = tmpSkybox;
}

std::vector<std::string> RendererManager::drawingEntityNames() {
    return(extractKeys(this->drawingEntityBuffer_));
}


// MODEL
Model* RendererManager::model(std::string name) {
    return(this->modelBuffer_[name]);
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
    return(this->materialBuffer_[name]);
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
    ma->shader("S_Default")->texture("T_Default");
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
    return(this->shaderBuffer_[name]);
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
    return(this->textureBuffer_[name]);
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



Camera* RendererManager::camera() {
    return(this->camera_);
}

glm::mat4 RendererManager::projection() {
    return(this->projection_);
}

void RendererManager::projection(glm::mat4 p) {
    this->projection_ = p;
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


void RendererManager::loadMTL(std::string filepath) {
    std::vector<std::string> names;
    std::vector<std::vector<float>*> ambient;
    std::vector<std::vector<float>*> diffuse;
    std::vector<std::vector<float>*> specular;
    std::vector<float> shininess;

    readMTL(filepath, &names, &ambient, &diffuse, &specular, &shininess);

    for (int i = 0; i < names.size(); i++) {
        printf("name: %s\n", names[i].c_str());
        printf("ambient: %f %f %f\n", (*ambient[i])[0], (*ambient[i])[1], (*ambient[i])[2]);
        printf("diffuse: %f %f %f\n", (*diffuse[i])[0], (*diffuse[i])[1], (*diffuse[i])[2]);
        printf("specular: %f %f %f\n", (*specular[i])[0], (*specular[i])[1], (*specular[i])[2]);
        printf("%f\n", shininess[i]);

        this->newMaterial(names[i])->ambient(glm::vec3((*ambient[i])[0], (*ambient[i])[1], (*ambient[i])[2]))->
                                     diffuse(glm::vec3((*diffuse[i])[0], (*diffuse[i])[1], (*diffuse[i])[2]))->
                                     specular(glm::vec3((*specular[i])[0], (*specular[i])[1], (*specular[i])[2]))->
                                     shininess(shininess[i]);
    }
}



// PRINTS
void RendererManager::printFullDE(std::string name) {
    printf("Drawing Entity: %s\n", name.c_str());
    this->drawingEntityBuffer_[name]->printFull();
    printf("\n");

    std::string model = this->drawingEntityBuffer_[name]->model();

    if (model.size() != 0) {
        this->printFullM(model);
    }

    printf("\n");

    std::string material = this->drawingEntityBuffer_[name]->material();

    if (material.size() != 0) {
        this->printFullMA(material);
    }
}

void RendererManager::printFullM(std::string name) {
    printf("Model: %s\n", name.c_str());
    this->modelBuffer_[name]->print();
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
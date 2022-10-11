#include "sandbox.h"

void sandbox() {
    RM.newShader("S_Lighting")->loadShader("../Shader/lighting/lighting.vert", "../Shader/lighting/lighting.frag");
    RM.newShader("S_LightingTex")->loadShader("../Shader/lightingTex/lightingTex.vert", "../Shader/lightingTex/lightingTex.frag");

    RM.newMesh("ME_Guy", "../Models/guy7.obj");
    RM.newModel("M_Guy")->mesh("ME_Guy")->shader("S_LightingTex")->translate(glm::vec3(-10.0f, 0.0f, 0.0f));

    RM.loadMTL("../Models/low_poly_tree/processed/untitled.mtl");
    RM.model(RM.loadModel("../Models/low_poly_tree/processed/untitled.obj", "M_Tree"))->translate(glm::vec3(10.0f, 0.0f, 0.0f))->shaders("S_Lighting");

    RM.loadMTL("../Models/gally/untitled.mtl");
    RM.model(RM.loadModel("../Models/gally/untitled.obj", "M_Gally"))->translate(glm::vec3(0.0f, 0.0f, -20.0f))->shaders("S_Lighting");

    RM.loadMTL("../Models/iryo/untitled.mtl");
    RM.model(RM.loadModel("../Models/iryo/untitled.obj", "M_Iryo"))->translate(glm::vec3(0.0f, 30.0f, 0.0f))->shaders("S_Lighting");

    RM.newShader("S_Reflection")->loadShader("../Shader/reflection/reflection.vert", "../Shader/reflection/reflection.frag");
    RM.shader("S_Reflection")->printFull();
    RM.newModel("M_Test")->mesh("ME_Sphere")->shaders("S_Reflection");
}


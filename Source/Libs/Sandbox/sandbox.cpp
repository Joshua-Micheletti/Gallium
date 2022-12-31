#include "sandbox.h"

void sandbox() {

    RM.newModel("Test");

    
    // REPLACE THIS CODE WITH ANYTHING YOU WANT TO BE LOADED IN THE ENGINE
    RM.newShader("S_Lighting")->loadShader("../Shader/lighting/lighting.vert", "../Shader/lighting/lighting.frag");
    RM.newShader("S_LightingTex")->loadShader("../Shader/lightingTex/lightingTex.vert", "../Shader/lightingTex/lightingTex.frag");
    RM.newShader("S_LightingMaterialTex")->loadShader("../Shader/lightingTex/lightingMaterialTex.vert", "../Shader/lightingTex/lightingMaterialTex.frag");

    RM.newShader("S_Reflection")->loadShader("../Shader/reflection/reflection.vert", "../Shader/reflection/reflection.frag");
    /*
    RM.shader("S_Reflection")->printFull();
    // RM.newModel("M_Test")->mesh("ME_Sphere")->shaders("S_Reflection");

    RM.newTexture("T_Box")->loadTexture("../Textures/container2.jpg");
    RM.newModel("TestBox")->shaders("S_LightingMaterialTex");
    RM.newTexture("T_BoxSpecular")->loadTexture("../Textures/container2_specular.jpg");
    RM.model("TestBox")->components()[0]->texture.specular("T_BoxSpecular");
    RM.model("TestBox")->components()[0]->texture.diffuse("T_Box");

    // RM.newTexture("T_ArmorSpecular")->loadTexture("../Models/Armor/textures/specular.jpg");
    // RM.loadMTL("../Models/Armor/skyrim.mtl");
    // RM.model(RM.loadModel("../Models/Armor/skyrim.obj", "Armor"))->shaders("S_LightingMaterialTex");
    // RM.model("Armor")->components()[0]->texture.specular("T_ArmorSpecular");
    // RM.model("Armor")->components()[0]->texture.diffuse("T_ArmorSpecular");
    // RM.model("Armor")->components()[0]->texture.general("T_ArmorSpecular");

    RM.newTexture("T_Halo")->loadTexture("../Models/halo/LP_Dif.jpg");
    RM.newTexture("T_HaloSpec")->loadTexture("../Models/halo/LP_Spec.jpg");
    RM.loadMTL("../Models/halo/VK78.mtl");
    RM.model(RM.loadModel("../Models/halo/VK78.obj", "Halo"))->shaders("S_LightingMaterialTex");

    for (int i = 0; i < RM.model("Halo")->components().size(); i++) {
        RM.model("Halo")->components()[i]->texture.diffuse("T_Halo");
        RM.model("Halo")->components()[i]->texture.specular("T_HaloSpec");
    }

    RM.newTexture("T_Hammer")->loadTexture("../Models/hammer/diffuse.jpg");
    RM.newTexture("T_HammerSpecular")->loadTexture("../Models/hammer/specular.jpg");
    RM.loadMTL("../Models/hammer/SLEDGE_hammer.mtl");
    RM.model(RM.loadModel("../Models/hammer/SLEDGE_hammer.obj", "M_Hammer"))->position(glm::vec3(10.0f))->shaders("S_LightingMaterialTex");

    PW.newPhysicsBody("P_Hammer");

    engine.link("P_Hammer", "M_Hammer");

    PW.newPhysicsBody("P_Halo")->mass(1000.0f)->position(glm::vec3(100.0f, 100.0f, 100.0f));

    engine.link("P_Halo", "Halo");


    RM.model("M_Hammer")->components()[0]->texture.diffuse("T_Hammer");
    RM.model("M_Hammer")->components()[0]->texture.specular("T_HammerSpecular");
    */
}


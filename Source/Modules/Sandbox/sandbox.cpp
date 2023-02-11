#include "sandbox.h"

void sandbox() {
    Timer sandboxSetupTimer;

    srand(clock());

    // REPLACE THIS CODE WITH ANYTHING YOU WANT TO BE LOADED IN THE ENGINE
    RM.newShader("S_Lighting")->loadShader("../Shader/lighting/lighting.vert", "../Shader/lighting/lighting.frag");
    RM.newShader("S_LightingTex")->loadShader("../Shader/lightingTex/lightingTex.vert", "../Shader/lightingTex/lightingTex.frag");
    RM.newShader("S_LightingMaterialTex")->loadShader("../Shader/lightingTex/lightingMaterialTex.vert", "../Shader/lightingTex/lightingMaterialTex.frag");

    RM.newShader("S_Reflection")->loadShader("../Shader/reflection/reflection.vert", "../Shader/reflection/reflection.frag");
    
    PW.newPhysicsBody("P_plane")->plane();

    for (int i = 0; i < 0; i++) {
        float x = rand() % 1000 / 100 - 5;
        float y = rand() % 3000 / 100 + 1;
        float z = rand() % 1000 / 100 - 5;

        PW.newPhysicsBody("P_sphere" + std::to_string(i))->sphere(1.0f, x, y, z);
        RM.newModel("M_Test" + std::to_string(i))->scale(glm::vec3(2, 2, 2))->mesh("ME_Sphere")->shader("S_LightingMaterialTex");
        engine.link("P_sphere" + std::to_string(i), "M_Test" + std::to_string(i));
    }

    for (int i = 0; i < 0; i++) {
        float x = rand() % 1000 / 100 - 5;
        float y = rand() % 3000 / 100 + 1;
        float z = rand() % 1000 / 100 - 5;

        PW.newPhysicsBody("P_Box" + std::to_string(i))->box(1.0f, x, y, z);
        RM.newModel("M_Box" + std::to_string(i))->scale(glm::vec3(0.5f, 0.5f, 0.5f))->shader("S_LightingMaterialTex");
        engine.link("P_Box" + std::to_string(i), "M_Box" + std::to_string(i));
    }

    // RM.newModel("M_Plane")->scale(glm::vec3(20.0f, 0.00001f, 20.0f))->shader("S_Lighting");
    
    PW.newPhysicsBody("P_Camera")->sphere();

    // RM.newMesh("ME_BoundingSphere", "../Models/Default/boundingSphere.obj");

    // float radius = RM.mesh("ME_Default")->radius();

    // RM.newModel("M_BoundingSphere")->mesh("ME_BoundingSphere")->scale(glm::vec3(radius, radius, radius));
    // // RM.newModel("M_TestCube")->shader("S_LightingMaterialTex");

    RM.newTexture("T_Halo")->loadTexture("../Models/halo/LP_Dif.jpg");
    RM.newTexture("T_HaloSpec")->loadTexture("../Models/halo/LP_Spec.jpg");
    RM.loadMTL("../Models/halo/VK78.mtl");
    RM.model(RM.loadModel("../Models/halo/VK78.obj", "Halo"))->shaders("S_LightingMaterialTex");

    for (int i = 0; i < RM.model("Halo")->components().size(); i++) {
        RM.model("Halo")->components()[i]->texture.diffuse("T_Halo");
        RM.model("Halo")->components()[i]->texture.specular("T_HaloSpec");
    }

    // RM.newModel("M_BoundingSphereHalo")->mesh("ME_BoundingSphere")->scale(glm::vec3())

    RM.loadMTL("../Models/skull/skull3.mtl");
    RM.model(RM.loadModel("../Models/skull/skull3.obj", "M_Skull"))->shaders("S_Lighting");

    RM.newTexture("T_Revolver")->loadTexture("../Models/revolver/textures/BaseColor.jpg");
    RM.newTexture("T_RevolverSpec")->loadTexture("../Models/revolver/textures/Metallic.jpg");

    RM.loadMTL("../Models/revolver/source/untitled.mtl");
    RM.model(RM.loadModel("../Models/revolver/source/untitled.obj", "M_Revolver"))->shaders("S_LightingMaterialTex");

    for (int i = 0; i < RM.model("M_Revolver")->components().size(); i++) {
        RM.model("M_Revolver")->components()[i]->texture.diffuse("T_Revolver");
        RM.model("M_Revolver")->components()[i]->texture.specular("T_RevolverSpec");
    }


    RM.newTexture("T_Rifle")->loadTexture("../Models/rifle/blender/textures/Sniper_KSR_29_Col.jpg");
    RM.newTexture("T_RifleSpec")->loadTexture("../Models/rifle/blender/textures/Sniper_KSR_29_spec.jpg");

    RM.loadMTL("../Models/rifle/sniper.mtl");
    RM.model(RM.loadModel("../Models/rifle/sniper.obj", "M_Rifle"))->shaders("S_LightingMaterialTex");

    for (int i = 0; i < RM.model("M_Rifle")->components().size(); i++) {
        RM.model("M_Rifle")->components()[i]->texture.diffuse("T_Rifle");
        RM.model("M_Rifle")->components()[i]->texture.specular("T_RifleSpec");
    }

    // REMOVE
    PW.updateBodies();

    // engine.link("sphere", "M_Test");
    
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

   printf("\n%sSetup scene%s\n", strGreen.c_str(), strNoColor.c_str());
   sandboxSetupTimer.print();
}


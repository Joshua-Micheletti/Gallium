#include "sandbox.h"

void sandbox() {
    Timer sandboxSetupTimer;

    srand(clock());

    // REPLACE THIS CODE WITH ANYTHING YOU WANT TO BE LOADED IN THE ENGINE
    RM.newShader("S_Lighting")->loadShader("../Shader/lighting/lighting.vert", "../Shader/lighting/lighting.frag");
    RM.newShader("S_LightingTex")->loadShader("../Shader/lightingTex/lightingTex.vert", "../Shader/lightingTex/lightingTex.frag");
    RM.newShader("S_LightingMaterialTex")->loadShader("../Shader/lightingTex/lightingMaterialTex.vert", "../Shader/lightingTex/lightingMaterialTex.frag");

    // RM.newShader("S_Reflection")->loadShader("../Shader/reflection/reflection.vert", "../Shader/reflection/reflection.frag");
    
    // PW.newPhysicsBody("P_plane")->plane();

    // for (int i = 0; i < 200; i++) {
    //     float x = rand() % 1000 / 100 - 5;
    //     float y = rand() % 3000 / 100 + 1;
    //     float z = rand() % 1000 / 100 - 5;

    //     PW.newPhysicsBody("P_sphere" + std::to_string(i))->sphere(1.0f, x, y, z);
    //     RM.newModel("M_Test" + std::to_string(i))->scale(glm::vec3(2, 2, 2))->mesh("ME_Sphere")->shader("S_Reflection");
    //     engine.link("P_sphere" + std::to_string(i), "M_Test" + std::to_string(i));
    // }

    // for (int i = 0; i < 200; i++) {
    //     float x = rand() % 1000 / 100 - 5;
    //     float y = rand() % 3000 / 100 + 1;
    //     float z = rand() % 1000 / 100 - 5;

    //     PW.newPhysicsBody("P_Box" + std::to_string(i))->box(1.0f, x, y, z);
    //     RM.newModel("M_Box" + std::to_string(i))->scale(glm::vec3(0.5f, 0.5f, 0.5f))->shader("S_Reflection");
    //     engine.link("P_Box" + std::to_string(i), "M_Box" + std::to_string(i));
    // }

    // RM.newModel("M_Plane")->scale(glm::vec3(20.0f, 0.00001f, 20.0f))->shader("S_Lighting");
    
    // PW.newPhysicsBody("P_Camera")->sphere();

    // RM.newMesh("ME_BoundingSphere", "../Models/Default/boundingSphere.obj");

    // float radius = RM.mesh("ME_Default")->radius();

    // RM.newModel("M_BoundingSphere")->mesh("ME_BoundingSphere")->scale(glm::vec3(radius, radius, radius));


    // RM.newSphere("SP_1", glm::vec3(0.5, 0.5, 0.5), 0.25)->materialIndex(0 + 2);
    // RM.newSphere("SP_light", glm::vec3(1, 1, 1), 0.25)->materialIndex(14 + 2);
    RM.newSphere("SP_0",  glm::vec3(-0.80, 1,   -0.80), 0.15)->materialIndex(0 + 2);
    RM.newSphere("SP_1",  glm::vec3(-0.80, 1,   -0.40), 0.15)->materialIndex(1 + 2);
    RM.newSphere("SP_2",  glm::vec3(-0.80, 1,   -0.00), 0.15)->materialIndex(2 + 2);
    RM.newSphere("SP_3",  glm::vec3(-0.80, 1,    0.40), 0.15)->materialIndex(3 + 2);
    RM.newSphere("SP_4",  glm::vec3(-0.80, 1,    0.80), 0.15)->materialIndex(4 + 2);
    RM.newSphere("SP_5",  glm::vec3(-0.40, 0.5, -0.80), 0.15)->materialIndex(5 + 2);
    RM.newSphere("SP_6",  glm::vec3(-0.40, 0.5, -0.40), 0.15)->materialIndex(6 + 2);
    RM.newSphere("SP_7",  glm::vec3(-0.40, 0.5, -0.00), 0.15)->materialIndex(7 + 2);
    RM.newSphere("SP_8",  glm::vec3(-0.40, 0.5,  0.40), 0.15)->materialIndex(8 + 2);
    RM.newSphere("SP_9",  glm::vec3(-0.40, 0.5,  0.80), 0.15)->materialIndex(9 + 2);
    RM.newSphere("SP_10", glm::vec3(-0.60, 0.75,-0.00), 0.15)->materialIndex(10 + 2);
    RM.newSphere("SP_11", glm::vec3(0, 3.95,-0.00), 2)->materialIndex(14 + 2);

    RM.newMaterial("aMA_White_Opaque")  ->diffuse(glm::vec3(1.0))->emissive(glm::vec3(0.0))->emissivness(0.0)->reflectivness(0.0)->specular(glm::vec3(1.0))->albedo(0.0); // 0
    RM.newMaterial("bMA_Red_0.2shine")  ->diffuse(glm::vec3(1.0, 0.2, 0.2))->emissive(glm::vec3(0.0, 0.0, 0.0))->emissivness(1.0)->reflectivness(0.2)->specular(glm::vec3(1.0, 0.2, 0.2))->albedo(1.0); // 1
    RM.newMaterial("cMA_Green_0.4shine")->diffuse(glm::vec3(0.2, 1.0, 0.2))->emissive(glm::vec3(0.0, 0.0, 0.0))->emissivness(1.0)->reflectivness(0.4)->specular(glm::vec3(0.2, 1.0, 0.2))->albedo(1.0); // 2
    RM.newMaterial("dMA_Blue_0.8shine") ->diffuse(glm::vec3(0.2, 0.2, 1.0))->emissive(glm::vec3(0.0, 0.0, 0.0))->emissivness(1.0)->reflectivness(0.6)->specular(glm::vec3(0.2, 0.2, 1.0))->albedo(1.0); // 3
    RM.newMaterial("eMA_White_0.8shine")->diffuse(glm::vec3(1.0, 1.0, 1.0))->emissive(glm::vec3(0.0, 0.0, 0.0))->emissivness(1.0)->reflectivness(0.8)->specular(glm::vec3(1.0, 1.0, 1.0))->albedo(1.0); // 4
    RM.newMaterial("fMA_White_1.0shine")->diffuse(glm::vec3(0.0, 0.0, 0.0))->emissive(glm::vec3(0.0, 0.0, 0.0))->emissivness(1.0)->reflectivness(1.0)->specular(glm::vec3(1.0, 1.0, 1.0))->albedo(1.0); // 5
    RM.newMaterial("gMA_Red_0.2albedo") ->diffuse(glm::vec3(1.0, 0.2, 0.2))->emissive(glm::vec3(0.0, 0.0, 0.0))->emissivness(1.0)->reflectivness(1.0)->specular(glm::vec3(1.0, 1.0, 1.0))->albedo(0.2); // 6
    RM.newMaterial("hMA_Green0.5albedo")->diffuse(glm::vec3(0.2, 1.0, 0.2))->emissive(glm::vec3(0.0, 0.0, 0.0))->emissivness(1.0)->reflectivness(1.0)->specular(glm::vec3(1.0, 1.0, 1.0))->albedo(0.5); // 7
    RM.newMaterial("iMA_Blue1.0albedo") ->diffuse(glm::vec3(0.2, 0.2, 1.0))->emissive(glm::vec3(0.0, 0.0, 0.0))->emissivness(1.0)->reflectivness(1.0)->specular(glm::vec3(1.0, 1.0, 1.0))->albedo(1.0); // 8
    RM.newMaterial("jMA_Red_Emit")      ->diffuse(glm::vec3(1.0, 1.0, 1.0))->emissive(glm::vec3(1.0, 0.2, 0.2))->emissivness(1.0)->reflectivness(0.0)->specular(glm::vec3(1.0, 1.0, 1.0))->albedo(0.0); // 9
    RM.newMaterial("k0MA_Green_Emit")    ->diffuse(glm::vec3(1.0, 1.0, 1.0))->emissive(glm::vec3(0.2, 1.0, 0.2))->emissivness(1.0)->reflectivness(0.0)->specular(glm::vec3(1.0, 1.0, 1.0))->albedo(0.0); // 10
    RM.newMaterial("l1MA_Red_Opaque")    ->diffuse(glm::vec3(1.0, 0.2, 0.2))->emissive(glm::vec3(0.0, 0.0, 0.0))->emissivness(1.0)->reflectivness(0.0)->specular(glm::vec3(1.0, 1.0, 1.0))->albedo(0.0); // 11
    RM.newMaterial("m2MA_Blue_Opaque")   ->diffuse(glm::vec3(0.2, 0.2, 1.0))->emissive(glm::vec3(0.0, 0.0, 0.0))->emissivness(1.0)->reflectivness(0.0)->specular(glm::vec3(1.0, 1.0, 1.0))->albedo(0.0); // 12
    RM.newMaterial("n3MA_Green_Opaque")  ->diffuse(glm::vec3(0.2, 1.0, 0.2))->emissive(glm::vec3(0.0, 0.0, 0.0))->emissivness(1.0)->reflectivness(0.0)->specular(glm::vec3(1.0, 1.0, 1.0))->albedo(0.0); // 13
    RM.newMaterial("o4MA_White_Emit")    ->diffuse(glm::vec3(1.0, 1.0, 1.0))->emissive(glm::vec3(1.0, 1.0, 1.0))->emissivness(2.0)->reflectivness(0.0)->specular(glm::vec3(1.0, 1.0, 1.0))->albedo(0.0); // 14

    for (std::string name : RM.materialNames()) {
        printf("%s\n", name.c_str());
    }

    RM.newPlane("P_Back", glm::vec3(0, 1, -1), glm::vec3(0, 0, 1))->materialIndex(11 + 2);
    RM.newPlane("P_Front", glm::vec3(0, 1, 1), glm::vec3(0, 0, -1))->materialIndex(12 + 2);
    RM.newPlane("P_Left", glm::vec3(-1, 1, 0), glm::vec3(1, 0, 0))->materialIndex(0 + 2);
    RM.newPlane("P_Right", glm::vec3(1, 1, 0), glm::vec3(-1, 0, 0))->materialIndex(0 + 2);
    RM.newPlane("P_Bottom", glm::vec3(0, 0, 0), glm::vec3(0, 1, 0))->materialIndex(13 + 2);
    RM.newPlane("P_Top", glm::vec3(0, 2, 1), glm::vec3(0, -1, 0))->materialIndex(0 + 2);
    
    // RM.newModel("M_TestSphere")->mesh("ME_Sphere")->shader("S_LightingMaterialTex");

    // RM.newTexture("T_Halo")->loadTexture("../Models/halo/LP_Dif.jpg");
    // RM.newTexture("T_HaloSpec")->loadTexture("../Models/halo/LP_Spec.jpg");
    // RM.loadMTL("../Models/halo/VK78.mtl");
    // RM.model(RM.loadModel("../Models/halo/VK78.obj", "Halo"))->shaders("S_LightingMaterialTex");

    // for (int i = 0; i < RM.model("Halo")->components().size(); i++) {
    //     RM.model("Halo")->components()[i]->texture.diffuse("T_Halo");
    //     RM.model("Halo")->components()[i]->texture.specular("T_HaloSpec");
    // }

    // // RM.newModel("M_BoundingSphereHalo")->mesh("ME_BoundingSphere")->scale(glm::vec3())

    // RM.loadMTL("../Models/skull/skull3.mtl");
    // RM.model(RM.loadModel("../Models/skull/skull3.obj", "M_Skull"))->shaders("S_Lighting");

    // RM.newTexture("T_Revolver")->loadTexture("../Models/revolver/textures/BaseColor.jpg");
    // RM.newTexture("T_RevolverSpec")->loadTexture("../Models/revolver/textures/Metallic.jpg");

    // RM.loadMTL("../Models/revolver/source/untitled.mtl");
    // RM.model(RM.loadModel("../Models/revolver/source/untitled.obj", "M_Revolver"))->shaders("S_LightingMaterialTex");

    // for (int i = 0; i < RM.model("M_Revolver")->components().size(); i++) {
    //     RM.model("M_Revolver")->components()[i]->texture.diffuse("T_Revolver");
    //     RM.model("M_Revolver")->components()[i]->texture.specular("T_RevolverSpec");
    // }


    // RM.newTexture("T_Rifle")->loadTexture("../Models/rifle/blender/textures/Sniper_KSR_29_Col.jpg");
    // RM.newTexture("T_RifleSpec")->loadTexture("../Models/rifle/blender/textures/Sniper_KSR_29_spec.jpg");

    // RM.loadMTL("../Models/rifle/sniper.mtl");
    // RM.model(RM.loadModel("../Models/rifle/sniper.obj", "M_Rifle"))->shaders("S_LightingMaterialTex");

    // for (int i = 0; i < RM.model("M_Rifle")->components().size(); i++) {
    //     RM.model("M_Rifle")->components()[i]->texture.diffuse("T_Rifle");
    //     RM.model("M_Rifle")->components()[i]->texture.specular("T_RifleSpec");
    // }

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


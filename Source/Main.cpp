#define GLFW_DLL
#include "Libs/lib.h"

void testFunc() {
	// RM.loadModel("../Models/guy7.obj", "M_Guy");
	// RM.newDrawingEntity("DE_Guy")->model("M_Guy")->translate(glm::vec3(-20.0f, 0.0f, 0.0f));

	// RM.loadModel("../Models/low_poly_tree/processed/untitled.obj", "M_Tree");
	// RM.loadMTL("../Models/low_poly_tree/processed/untitled.mtl");

	// RM.newDrawingEntity("DE_Tree")->model("M_Tree");

	std::vector<std::vector<float>*> v;
    std::vector<std::vector<float>*> t;
    std::vector<std::vector<float>*> n;
    std::vector<std::string> m;

    readOBJ("../Models/guy7.obj", &v, &t, &n, &m);

    RM.newMesh("ME_Guy")->vertices((*v[0]))->uvs((*t[0]))->normals((*n[0]));
	RM.newShader("S_Lighting")->loadShader("../Shader/lighting/lighting.vert", "../Shader/lighting/lighting.frag");
	RM.newShader("S_White")->loadShader("../Shader/white/white.vert", "../Shader/white/white.frag");

	RM.newModel("M_Guy")->components()[0]->mesh = "ME_Guy";
	RM.model("M_Guy")->components()[0]->shader = "S_Lighting";

	RM.loadModel("../Models/low_poly_tree/processed/untitled.obj", "M_Tree");
	
	std::vector<std::string> materials = RM.loadMTL("../Models/low_poly_tree/processed/untitled.mtl");

	RM.model("M_Tree")->shaders("S_Lighting");
	RM.model("M_Tree")->components()[0]->material = materials[0];
	RM.model("M_Tree")->components()[1]->material = materials[1];


	// printf("%s\n", RM.newDrawingEntity("DE_Test")->model().c_str());
	// RM.model(RM.newDrawingEntity("DE_Test")->model())->meshes()[0]->shader = "S_Lighting";
	// RM.model(RM.drawingEntity("DE_Test")->model())->meshes()[0]->mesh = "ME_Guy";
}

int main(void) {
	Renderer renderer;
	EventHandler eventHandler(window.window());
	UI interface(&renderer, &eventHandler);

	testFunc();
	while (!glfwWindowShouldClose(window.window())) {
		eventHandler.routine();
		renderer.render();
		interface.drawInfo();

		glfwPollEvents();
		glfwSwapBuffers(window.window());
	}

	glfwTerminate();
	return(0);
}




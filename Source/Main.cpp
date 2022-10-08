#define GLFW_DLL
#include "Libs/lib.h"

void testFunc() {
	RM.newShader("S_Lighting")->loadShader("../Shader/lighting/lighting.vert", "../Shader/lighting/lighting.frag");
	RM.newShader("S_LightingTex")->loadShader("../Shader/lightingTex/lightingTex.vert", "../Shader/lightingTex/lightingTex.frag");

	RM.newMesh("ME_Guy", "../Models/guy7.obj");
	RM.newModel("M_Guy")->mesh("ME_Guy")->shader("S_LightingTex")->translate(glm::vec3(-10.0f, 0.0f, 0.0f));

	RM.loadMTL("../Models/low_poly_tree/processed/untitled.mtl");
	RM.model(RM.loadModel("../Models/low_poly_tree/processed/untitled.obj", "M_Tree"))->translate(glm::vec3(10.0f, 0.0f, 0.0f))->shaders("S_Lighting");

	RM.loadMTL("../Models/gally/untitled.mtl");
	RM.model(RM.loadModel("../Models/gally/untitled.obj", "M_Gally"))->translate(glm::vec3(0.0f, 0.0f, -20.0f))->shaders("S_Lighting");

	// RM.model("M_Gally")->shaders("S_Lighting");
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




#define GLFW_DLL
#include "Libs/lib.h"

void testFunc() {
	RM.newModel("M_Test")->loadModel("../Models/guy7.obj");
	RM.newShader("S_Test")->loadShader("../Shader/lighting/lighting.vert", "../Shader/lighting/lighting.frag");
	RM.newMaterial("MA_Test")->shader("S_Test");
	RM.newDrawingEntity("DE_Test")->model("M_Test")->material("MA_Test");

	RM.drawingEntity("DE_Test")->translate(glm::vec3(0.0f, 0.0f, 0.0f))->scale(glm::vec3(2.0, 2.0, 2.0));
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




#define GLFW_DLL
#include "Libs/lib.h"

void testFunc() {
	RM.newModel("M_Test")->loadModel("../Models/sphere7.obj");
	RM.newShader("S_Test")->loadShader("../Shader/lightingTex/lightVertexTexture.c", "../Shader/lightingTex/lightFragmentTexture.c");
	RM.newTexture("T_Test")->loadTexture("../Textures/default2.jpg");
	RM.newMaterial("MA_Test")->shader("S_Test")->texture("T_Test");
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

		printf("new frame\n");

		glfwPollEvents();
		glfwSwapBuffers(window.window());
	}

	glfwTerminate();
	return(0);
}




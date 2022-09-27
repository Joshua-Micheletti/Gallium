#define GLFW_DLL
#include "Libs/lib.h"

void testFunc() {
	RM.newModel("M_Test")->loadModel("../Models/box2.obj");
	RM.newShader("S_Test")->loadShader("../Shader/lightingTex/lightVertexTexture.c", "../Shader/lightingTex/lightFragmentTexture.c");
	// RM.newTexture("T_Test")->loadTexture("../Textures/fi_uv_4096__display_grid_8x8_32x32_128x128_by_fisholith-d786zt5.png");
	RM.newTexture("T_Test")->loadTexture("../Textures/default2.jpg");
	RM.newMaterial("MA_Test")->shader("S_Test")->texture("T_Test");
	RM.newDrawingEntity("DE_Test")->model("M_Test")->material("MA_Test");

	RM.drawingEntity("DE_Test")->translate(glm::vec3(10.0f, 8.0f, 5.0f));
	// RM.drawingEntity("DE_Test")->scale(glm::vec3(4.0f, 4.0f, 0.5f));
	// RM.drawingEntity("DE_Test")->rotate(glm::vec3(10.0f, 5.0f, 2.0f));
	RM.drawingEntity("DE_Test")->translate(glm::vec3(10.0f, 0.0f, 0.0f));

	RM.newModel("M_Light")->loadModel("../Models/sphere7.obj");
	RM.newShader("S_Light")->loadShader("../Shader/white/white.vert", "../Shader/white/white.frag");
	RM.newMaterial("MA_Light")->shader("S_Light");
	RM.newDrawingEntity("DE_Light")->model("M_Light")->material("MA_Light");

	RM.drawingEntity("DE_Light")->model("M_Light");
	RM.drawingEntity("DE_Light")->material("MA_Light");
}

int main(void) {
	//GLFWwindow* window = setup();
	// Window window;
	// RendererManager RM;
	Renderer renderer;
	//EventHandler eventHandler(window);
	EventHandler eventHandler(window.getWindow());
	// //UI interface(window, &renderer, &eventHandler);
	// UI interface(window.getWindow(), &renderer, &eventHandler);

	testFunc();
	while (!glfwWindowShouldClose(window.getWindow())) {
	// //while (!glfwWindowShouldClose(window)) {
		eventHandler.routine();
		// printf("%p\n", RM.drawingEntity(RM.skybox()));
		renderer.render();
		// printf("%p\n", RM.drawingEntity(RM.skybox()));
		
	// 	// interface.drawInfo();
		
		glfwPollEvents();
		glfwSwapBuffers(window.getWindow());
		//glfwSwapBuffers(window);
	}

	glfwTerminate();
	return(0);
}




#define GLFW_DLL
#include "Libs/lib.h"

void testFunc() {
	RM.newDrawingEntity("DE_Test");

	RM.newModel("M_Test");
	RM.model("M_Test")->loadModel("../Models/box2.obj");
	RM.drawingEntity("DE_Test")->model("M_Test");

	RM.newMaterial("MA_Test");

	RM.newShader("S_Test");
	RM.shader("S_Test")->loadShader("../Shader/shader1/vertex.c", "../Shader/shader1/fragment.c");
	RM.material("MA_Test")->shader("S_Test");

	RM.newTexture("T_Test");
	RM.texture("T_Test")->loadTexture("../Textures/fi_uv_4096__display_grid_8x8_32x32_128x128_by_fisholith-d786zt5.png");
	RM.material("MA_Test")->texture("T_Test");
	
	RM.drawingEntity("DE_Test")->material("MA_Test");
	RM.printFullDE("DE_Test");

	RM.drawingEntity("DE_Test")->translate(glm::vec3(10.0f, 8.0f, 5.0f));
	RM.drawingEntity("DE_Test")->scale(glm::vec3(4.0f, 4.0f, 0.5f));
	RM.drawingEntity("DE_Test")->rotate(glm::vec3(10.0f, 5.0f, 2.0f));

	RM.newDrawingEntity("DE_Light");
	RM.newModel("M_Light");
	RM.model("M_Light")->loadModel("../Models/sphere7.obj");

	RM.newMaterial("MA_Light");
	RM.newShader("S_Light");

	std::vector<DrawingEntity*> drawingEntities = RM.drawingEntities();
	
	for (int i = 0; i < drawingEntities.size(); i++) {
		drawingEntities[i]->printFull();
	}
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
		renderer.render();
		
	// 	// interface.drawInfo();
		
		glfwPollEvents();
		glfwSwapBuffers(window.getWindow());
		//glfwSwapBuffers(window);
	}

	glfwTerminate();
	return(0);
}




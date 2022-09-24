#define GLFW_DLL
#include "Libs/lib.h"


void testFunc() {
	DrawingEntity de;
	Model m;
	Material ma;
	Shader s;

	m.loadModel("../Models/box2.obj");

	RM.drawingEntity("DE_Test", &de);
	RM.model("M_Test", &m);
	RM.drawingEntity("DE_Test")->setModel("M_Test");
	RM.shader("S_Test", &s);
	RM.material("MA_Test", &ma);
	RM.material("MA_Test")->shader("S_Test");
	RM.drawingEntity("DE_Test")->setMaterial("MA_Test");
	RM.printFullDE("DE_Test");
}

int main(void) {
	//GLFWwindow* window = setup();
	// Window window;
	// RendererManager RM;
	//Renderer renderer;
	//EventHandler eventHandler(window);
	EventHandler eventHandler(window.getWindow());
	// //UI interface(window, &renderer, &eventHandler);
	// UI interface(window.getWindow(), &renderer, &eventHandler);

	testFunc();
	while (!glfwWindowShouldClose(window.getWindow())) {
	// //while (!glfwWindowShouldClose(window)) {
		eventHandler.routine();
	// 	renderer.render();
		
	// 	// interface.drawInfo();
		
		glfwPollEvents();
		glfwSwapBuffers(window.getWindow());
		//glfwSwapBuffers(window);
	}

	glfwTerminate();
	return(0);
}




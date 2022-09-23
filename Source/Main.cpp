#define GLFW_DLL
#include "Libs/lib.h"

void testFunc() {
	DrawingEntity de;
	de.model()->loadModel("../Models/box2.obj");
	de.printFull();
}

int main(void) {
	//GLFWwindow* window = setup();
	Window window;
	Renderer renderer;
	//EventHandler eventHandler(window);
	EventHandler eventHandler(window.getWindow());
	//UI interface(window, &renderer, &eventHandler);
	UI interface(window.getWindow(), &renderer, &eventHandler);

	testFunc();
	while (!glfwWindowShouldClose(window.getWindow())) {
	//while (!glfwWindowShouldClose(window)) {
		eventHandler.routine();
		renderer.render();
		
		// interface.drawInfo();
		
		glfwPollEvents();
		glfwSwapBuffers(window.getWindow());
		//glfwSwapBuffers(window);
	}

	glfwTerminate();
	return(0);
}




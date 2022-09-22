#define GLFW_DLL
#include "Libs/lib.h"

void testFunc() {
	Model test;
	test.loadModel("../Models/box2.obj");
	test.printFull();
	test.printFace(2);

}

int main(void) {
	GLFWwindow* window = setup();
	Renderer renderer;
	EventHandler eventHandler(window);
	UI interface(window, &renderer, &eventHandler);

	testFunc();
	
	while (!glfwWindowShouldClose(window)) {
		eventHandler.routine();
		renderer.render();
		interface.drawInfo();
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	return(0);
}




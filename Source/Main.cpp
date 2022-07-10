#define GLFW_DLL
#include "Libs/lib.h"

int main(void) {
	GLFWwindow* window = setup();
	Renderer renderer;
	EventHandler eventHandler(window);
	UI interface(window, &renderer, &eventHandler);

	printf("test main\n");

	while (!glfwWindowShouldClose(window)) {
		eventHandler.routine();
		renderer.render();
		interface.drawInfo();
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	return(0);
}




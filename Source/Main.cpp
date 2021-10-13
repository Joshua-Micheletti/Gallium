#include "Libs/lib.h"

int main(void) {
	GLFWwindow* window = setup();
	Renderer renderer;
	EventHandler eventHandler(window);
	UI interface(window, &renderer, &eventHandler);

	while (!glfwWindowShouldClose(window)) {
		eventHandler.routine();
		renderer.render();
		interface.drawInfo();
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	return(0);
}




#define GLFW_DLL
#include "Libs/lib.h"

int main(void) {
	Renderer renderer;
	EventHandler eventHandler(window.window());
	UI interface(&renderer, &eventHandler);

	sandbox();

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




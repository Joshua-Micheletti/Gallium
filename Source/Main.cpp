#define GLFW_DLL
#include "Libs/lib.h"

int main(void) {
	Renderer renderer;
	EventHandler eventHandler(window.window());
	UI interface(&renderer, &eventHandler);

	sandbox();

	while (!glfwWindowShouldClose(window.window())) {
		eventHandler.routine();
		PW.step(1.0f / 60.0f);
		engine.update(RM, PW);
		renderer.render();
		interface.drawInfo();
		glfwPollEvents();
		glfwSwapBuffers(window.window());
	}

	glfwTerminate();
	return(0);
}




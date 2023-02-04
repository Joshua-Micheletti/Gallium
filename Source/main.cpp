#define GLFW_DLL
#include "Modules/Utils/include.h"

int main(void) {
	Renderer renderer;
	EventHandler eventHandler(window.window());
	UI interface(&renderer, &eventHandler);

	sandbox();
	
	printf("\n%sTotal:\n", strGreen.c_str());
	setupTimer.print();

	while (!glfwWindowShouldClose(window.window())) {
		eventHandler.routine();
		PW.step();
		engine.update(RM, PW);
		renderer.render();
		interface.drawInfo();
		glfwPollEvents();
		glfwSwapBuffers(window.window());
	}

	glfwTerminate();
	return(0);
}




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
		debugger.print("NEW FRAME", "M");
		eventHandler.routine();
		debugger.print("HANDLED INPUTS", "M");
		PW.step();
		debugger.print("STEPPED PHYSICS", "M");
		engine.update(RM, PW);
		debugger.print("UPDATED THE ENGINE", "M");
		renderer.render();
		debugger.print("RENDERED THE FRAME", "M");
		interface.drawInfo();
		debugger.print("DRAWN THE UI", "M");
		glfwPollEvents();
		glfwSwapBuffers(window.window());
	}

	glfwTerminate();
	return(0);
}




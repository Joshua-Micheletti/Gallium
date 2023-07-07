#define GLFW_DLL
#include "Modules/Utils/include.h"

int main(void) {
	// Renderer renderer;
	PathTraceRenderer PTRenderer;
	EventHandler eventHandler(window.window());
	// UI interface(&renderer, &eventHandler);

	sandbox();
	
	printf("\n%sTotal:\n", strGreen.c_str());
	setupTimer.print();

	while (!glfwWindowShouldClose(window.window())) {
		double start = glfwGetTime();
		debugger.print("NEW FRAME", "M");
		eventHandler.routine();
		debugger.print("HANDLED INPUTS", "M");
		// PW.step();
		debugger.print("STEPPED PHYSICS", "M");
		// engine.update(RM, PW);
		debugger.print("UPDATED THE ENGINE", "M");
		PTRenderer.render();
		debugger.print("RENDERED THE FRAME", "M");
		// interface.drawInfo();
		debugger.print("DRAWN THE UI", "M");
		glfwPollEvents();
		glfwSwapBuffers(window.window());

		double end = glfwGetTime();

		printf("Total: %lf\n", (end - start) * 1000);
		printf("FPS: %lf\n", 1.0 / (end - start));
	}

	glfwTerminate();
	return(0);
}




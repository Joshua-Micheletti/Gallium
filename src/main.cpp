// #define GLFW_DLL
#include "modules/Utils/include.h"

int main(void) {
	// raster renderer
	Renderer renderer;
	// path tracing renderer
	PathTraceRenderer PTRenderer;
	// controller
	EventHandler eventHandler(window.window());
	// ui interface
	UI interface(&renderer, &eventHandler);

	// setup scene
	sandbox();
	
	printf("\n%sTotal:\n", strGreen.c_str());
	setupTimer.print();

	// main loop
	while (!glfwWindowShouldClose(window.window())) {
		double start = glfwGetTime();
		debugger.print("NEW FRAME", "M");
		// update things in the controller
		eventHandler.routine();
		debugger.print("HANDLED INPUTS", "M");
		// physics step update
		PW.step();
		debugger.print("STEPPED PHYSICS", "M");
		// update the entities (link between physics and render)
		engine.update(RM, PW);
		debugger.print("UPDATED THE ENGINE", "M");

		// render
		if (RM.pathTrace()) {
			PTRenderer.render();
		} else {
			renderer.render();
		}

		debugger.print("RENDERED THE FRAME", "M");
		// draw the UI interface
		interface.drawInfo();
		debugger.print("DRAWN THE UI", "M");

		// poll events from the window manager
		glfwPollEvents();
		// swap the gpu buffer
		glfwSwapBuffers(window.window());


		double end = glfwGetTime();
		printf("Total: %lf\n", (end - start) * 1000);
		printf("FPS: %lf\n", 1.0 / (end - start));
	}

	glfwTerminate();
	return(0);
}




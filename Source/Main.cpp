#define GLFW_DLL
#include "Libs/lib.h"

void testFunc() {
	// RM.newModel("M_Test")->loadModel("../Models/guy7.obj");
	// RM.newModel("M_Test")->loadModel("../Models/low_poly_tree/processed/untitled.obj");
	// RM.newModel("M_Test")->loadModel("../Models/box2.obj");
	// RM.newShader("S_Test")->loadShader("../Shader/lighting/lighting.vert", "../Shader/lighting/lighting.frag");
	RM.newShader("S_Test")->loadShader("../Shader/white/white.vert", "../Shader/white/white.frag");
	RM.newMaterial("MA_Test")->shader("S_Test");

	RM.loadModel("../Models/low_poly_tree/processed/untitled.obj", "M_Tree");
	RM.loadModel("../Models/guy7.obj", "M_Tree");

	RM.mesh(RM.model("M_Tree")->meshes()[0])->material("MA_Test");

	// for (int i = 0; i < RM.model("M_Tree")->meshes().size(); i++) {
	// 	RM.mesh(RM.model("M_Tree")->meshes()[i])->material("MA_Test");
	// }

	// RM.material("M_Tree", "MA_Test");

	RM.newDrawingEntity("DE_Tree")->model("M_Tree");
	// RM.mesh(RM.model("M_Tree")->meshes()[0])->material("Bark");
	// RM.mesh(RM.model("M_Tree")->meshes()[1])->material("Tree");
	// RM.newDrawingEntity("DE_Test")->model("M_Test")->material("MA_Test");

	// RM.drawingEntity("DE_Test")->translate(glm::vec3(0.0f, 0.0f, 0.0f))->scale(glm::vec3(2.0, 2.0, 2.0));

	// RM.applyMaterials(RM.model("M_Tree")->meshes(), RM.loadMTL("../Models/low_poly_tree/processed/untitled.mtl"));
}

int main(void) {
	Renderer renderer;
	EventHandler eventHandler(window.window());
	UI interface(&renderer, &eventHandler);

	testFunc();
	while (!glfwWindowShouldClose(window.window())) {
		eventHandler.routine();
		printf("about to render\n");
		renderer.render();
		interface.drawInfo();

		glfwPollEvents();
		glfwSwapBuffers(window.window());
	}

	glfwTerminate();
	return(0);
}




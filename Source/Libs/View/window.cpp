#include "window.h"

void errorCallback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

Window::Window() {
    if (!glfwInit()) {
        printf("%sError initializing GLFW%s\n", strRed.c_str(), strNoColor.c_str());
    }

	this->window = glfwCreateWindow(1280, 720, "3DEngine", NULL, NULL);
	
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	gladLoadGL();
	glEnable(GL_MULTISAMPLE);
	//glfwSetWindowSizeCallback(window, resizeCallback);
    glfwSetErrorCallback(errorCallback);
}

GLFWwindow* Window::getWindow() {
    return(this->window);
}


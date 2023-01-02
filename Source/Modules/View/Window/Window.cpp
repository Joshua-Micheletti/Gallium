#include "Window.h"

void errorCallback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

void resizeCallback(GLFWwindow* windowObj, int x, int y) {
	int width;
	int height;
	glfwGetFramebufferSize(windowObj, &width, &height);

	glViewport(0, 0, width, height);
	
	updateResolution = true;
}

Window::Window() {
    if (!glfwInit()) {
        printf("%sError initializing GLFW%s\n", strRed.c_str(), strNoColor.c_str());
    }

	this->m_width = 1280;
	this->m_height = 720;

	this->m_window = glfwCreateWindow(this->m_width, this->m_height, "3DEngine", NULL, NULL);
	
	glfwMakeContextCurrent(this->m_window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	glfwSetInputMode(this->m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	gladLoadGL();
	glEnable(GL_MULTISAMPLE);
	glfwSetWindowSizeCallback(this->m_window, resizeCallback);
    glfwSetErrorCallback(errorCallback);
}

GLFWwindow* Window::window() {
    return(this->m_window);
}


int Window::width() {
	updateWindowSize();
	return(this->m_width);
}

int Window::height() {
	updateWindowSize();
	return(this->m_height);
}

int Window::framebufferWidth() {
	updateFramebufferSize();
	return(this->m_framebufferWidth);
}

int Window::framebufferHeight() {
	updateFramebufferSize();
	return(this->m_framebufferHeight);
}


void Window::width(int width) {
	this->m_width = width;
} 

void Window::height(int height) {
	this->m_height = height;
}


void Window::updateWindowSize() {
	glfwGetWindowSize(this->m_window, &this->m_width, &this->m_height);
}

void Window::updateFramebufferSize() {
	glfwGetFramebufferSize(this->m_window, &this->m_framebufferWidth, &this->m_framebufferHeight);
}


void Window::fullscreen(bool f) {
	if (this->m_fullscreen != f) {
		if (f == true) {
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			glfwSetWindowMonitor(this->m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
			int width;
			int height;
			glfwGetFramebufferSize(this->m_window, &width, &height);
			glViewport(0, 0, mode->width, mode->height);
			this->m_updateResolution = true;
		}
		else {
			glfwSetWindowMonitor(this->m_window, NULL, 0, 0, 1280, 720, 60);
			glfwSetWindowPos(this->m_window, 40, 40);
			int width;
			int height;
			glfwGetFramebufferSize(this->m_window, &width, &height);
			glViewport(0, 0, width, height);
			this->m_updateResolution = true;
		}
	}

	this->m_fullscreen = f;
}

bool Window::fullscreen() {
	return(this->m_fullscreen);
}
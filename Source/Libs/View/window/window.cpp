#include "window.h"

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

	this->width_ = 1280;
	this->height_ = 720;

	this->window_ = glfwCreateWindow(this->width_, this->height_, "3DEngine", NULL, NULL);
	
	glfwMakeContextCurrent(this->window_);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	glfwSetInputMode(this->window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	gladLoadGL();
	glEnable(GL_MULTISAMPLE);
	glfwSetWindowSizeCallback(this->window_, resizeCallback);
    glfwSetErrorCallback(errorCallback);
}

GLFWwindow* Window::window() {
    return(this->window_);
}


int Window::width() {
	updateWindowSize();
	return(this->width_);
}

int Window::height() {
	updateWindowSize();
	return(this->height_);
}

int Window::framebufferWidth() {
	updateFramebufferSize();
	return(this->framebufferWidth_);
}

int Window::framebufferHeight() {
	updateFramebufferSize();
	return(this->framebufferHeight_);
}


void Window::width(int width) {
	this->width_ = width;
} 

void Window::height(int height) {
	this->height_ = height;
}


void Window::updateWindowSize() {
	glfwGetWindowSize(this->window_, &this->width_, &this->height_);
}

void Window::updateFramebufferSize() {
	glfwGetFramebufferSize(this->window_, &this->framebufferWidth_, &this->framebufferHeight_);
}


void Window::fullscreen(bool f) {
	if (this->fullscreen_ != f) {
		if (f == true) {
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			glfwSetWindowMonitor(this->window_, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
			int width;
			int height;
			glfwGetFramebufferSize(this->window_, &width, &height);
			glViewport(0, 0, mode->width, mode->height);
			this->updateResolution_ = true;
		}
		else {
			glfwSetWindowMonitor(this->window_, NULL, 0, 0, 1280, 720, 60);
			glfwSetWindowPos(this->window_, 40, 40);
			int width;
			int height;
			glfwGetFramebufferSize(this->window_, &width, &height);
			glViewport(0, 0, width, height);
			this->updateResolution_ = true;
		}
	}

	this->fullscreen_ = f;
}

bool Window::fullscreen() {
	return(this->fullscreen_);
}
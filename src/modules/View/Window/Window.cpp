#include "Window.hpp"

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

// window constructor method
Window::Window(int width, int height, std::string title) {
	// try to initialize glfw
    if (!glfwInit()) {
        printf("%sError initializing GLFW%s\n", strRed.c_str(), strNoColor.c_str());
    }

	// initial window size
	this->m_width = width;
	this->m_height = height;

	// create the glfw window object
	this->m_window = glfwCreateWindow(this->m_width, this->m_height, title.c_str(), NULL, NULL);
	
	// intialize the OpenGL context for glfw
	glfwMakeContextCurrent(this->m_window);
	// disable the cursor in the glfw window
	glfwSetInputMode(this->m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// load opengl functions
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	gladLoadGL();

	// enable multisampling
	// glEnable(GL_MULTISAMPLE);

	// set callback functions
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
Window* Window::width(int width) {
	this->m_width = width;
	return(this);
} 

int Window::height() {
	updateWindowSize();
	return(this->m_height);
}
Window* Window::height(int height) {
	this->m_height = height;
	return(this);
}

int Window::framebufferWidth() {
	updateFramebufferSize();
	return(this->m_framebufferWidth);
}
int Window::framebufferHeight() {
	updateFramebufferSize();
	return(this->m_framebufferHeight);
}


void Window::updateWindowSize() {
	glfwGetWindowSize(this->m_window, &this->m_width, &this->m_height);
}

void Window::updateFramebufferSize() {
	glfwGetFramebufferSize(this->m_window, &this->m_framebufferWidth, &this->m_framebufferHeight);
}


Window* Window::fullscreen(bool f) {
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
	
	return(this);
}

bool Window::fullscreen() {
	return(this->m_fullscreen);
}
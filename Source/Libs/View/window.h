#ifndef __WINDOW__
#define __WINDOW__

#include <glad/glad.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "../utils.h"

class Window {
    public:
        Window();
        GLFWwindow* getWindow();

    private:
        GLFWwindow* window;
};


#endif
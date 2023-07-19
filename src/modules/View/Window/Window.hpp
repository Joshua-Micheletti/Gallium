#ifndef __WINDOW__
#define __WINDOW__

#include <stdio.h>

#include <glad/glad.h>
// #define GLFW_DLL
#include <GLFW/glfw3.h>

#include "../../Utils/utils.h"

// window class
class Window {
    public:
        // constructor
        Window(int width = 1280, int height = 720, std::string title = "Gallium");
        
        // getter for the glfw window object
        GLFWwindow* window();

        // width getter / setter
        int width();
        Window* width(int);

        // height getter / setter
        int height();
        Window* height(int);

        // frame size getters
        int frameWidth();
        int frameHeight();
        
        // framebuffer size getters
        int framebufferWidth();
        int framebufferHeight();

        // fullscreen mode getter / setter
        bool fullscreen();
        Window* fullscreen(bool);

        // update resolution flag getter / setter
        bool updateResolution();
        Window* updateResolution(bool);

        // updated resolution flag getter / setter
        bool resolutionUpdated();
        Window* resolutionUpdated(bool);

    private:
        // glfw window object
        GLFWwindow* m_window;
        // window size
        int m_width;
        int m_height;
        // frame size
        int m_frameWidth;
        int m_frameHeight;
        // framebuffer size
        int m_framebufferWidth;
        int m_framebufferHeight;

        // window parameter flags
        bool m_fullscreen;

        // update flags
        bool m_updateResolution;
        bool m_resolutionUpdated;

        // private windows for updating the size of the window
        void updateWindowSize();
        // frame
        void updateFrameSize();
        // and framebuffer size
        void updateFramebufferSize();
};


#endif
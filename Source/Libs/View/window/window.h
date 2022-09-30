#ifndef __WINDOW__
#define __WINDOW__

#include <glad/glad.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "../../utils.h"

class Window {
    public:
        Window();
        GLFWwindow* window();

        int width();
        int height();

        int frameWidth();
        int frameHeight();
        
        int framebufferWidth();
        int framebufferHeight();

        void width(int);
        void height(int);

        bool fullscreen();
        void fullscreen(bool);

        bool updateResolution();
        void updateResolution(bool);

        bool resolutionUpdated();
        void resolutionUpdated(bool);

    private:
        GLFWwindow* window_;
        int width_;
        int height_;
        int frameWidth_;
        int frameHeight_;
        int framebufferWidth_;
        int framebufferHeight_;

        bool fullscreen_;

        bool updateResolution_;
        bool resolutionUpdated_;

        void updateWindowSize();
        void updateFrameSize();
        void updateFramebufferSize();
};


#endif
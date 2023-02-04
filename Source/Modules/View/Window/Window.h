#ifndef __WINDOW__
#define __WINDOW__

#include <stdio.h>

#include <glad/glad.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include "../../Utils/utils.h"

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
        GLFWwindow* m_window;
        int m_width;
        int m_height;
        int m_frameWidth;
        int m_frameHeight;
        int m_framebufferWidth;
        int m_framebufferHeight;

        bool m_fullscreen;

        bool m_updateResolution;
        bool m_resolutionUpdated;

        void updateWindowSize();
        void updateFrameSize();
        void updateFramebufferSize();
};


#endif
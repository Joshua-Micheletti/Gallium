#ifndef __DEBUGGER__
#define __DEBUGGER__

#include <string>

#include "utils.h"

class Debugger{
    public:
        Debugger();
        Debugger* debugRendererManager(bool);
        Debugger* debugRenderer(bool);
        Debugger* displayBoundingSpheres(bool);

        bool debugRendererManager();
        bool debugRenderer();
        bool displayBoundingSpheres();

        Debugger* printRM(std::string);

    private:
        bool m_debugRendererManager;
        bool m_debugRenderer;
        bool m_displayBoundingSpheres;
};

extern Debugger debugger;

#endif
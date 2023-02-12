#ifndef __DEBUGGER__
#define __DEBUGGER__

#include <string>

#include "utils.h"

class Debugger{
    public:
        Debugger();
        
        Debugger* debugRendererManager(bool);
        Debugger* debugRenderer(bool);
        Debugger* debugPhysicsWorld(bool);
        Debugger* debugMain(bool);
        Debugger* displayBoundingSpheres(bool);
        
        bool debugRendererManager();
        bool debugRenderer();
        bool debugPhysicsWorld();
        bool debugMain();
        bool displayBoundingSpheres();

        Debugger* print(std::string, std::string);

    private:
        bool m_debugRendererManager;
        bool m_debugRenderer;
        bool m_debugPhysicsWorld;
        bool m_debugMain;
        bool m_displayBoundingSpheres;
};

extern Debugger debugger;

#endif
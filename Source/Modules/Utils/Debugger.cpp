#include "Debugger.h"

Debugger::Debugger() {
    this->m_debugRenderer = true;
    this->m_debugRendererManager = true;
    this->m_debugPhysicsWorld = false;
    this->m_displayBoundingSpheres = false;
}


Debugger* Debugger::debugRenderer(bool debug) {
    this->m_debugRenderer = debug;
    return(this);
}
Debugger* Debugger::debugRendererManager(bool debug) {
    this->m_debugRendererManager = debug;
    return(this);
}
Debugger* Debugger::displayBoundingSpheres(bool debug) {
    this->m_displayBoundingSpheres = debug;
    return(this);
}
Debugger* Debugger::debugPhysicsWorld(bool debug) {
    this->m_debugPhysicsWorld = debug;
    return(this);
}


bool Debugger::debugRenderer() {
    return(this->m_debugRenderer);
}
bool Debugger::debugRendererManager() {
    return(this->m_debugRendererManager);
}
bool Debugger::debugPhysicsWorld() {
    return(this->m_debugPhysicsWorld);
}
bool Debugger::displayBoundingSpheres() {
    return(this->m_displayBoundingSpheres);
}


Debugger* Debugger::print(std::string text, std::string subject) {
    if (subject == "RM") {
        if (this->m_debugRendererManager) {
            printf("RM: %s%s%s\n", strPink.c_str(), text.c_str(), strNoColor.c_str());
        }
    }

    if (subject == "R") {
        if (this->m_debugRenderer) {
            printf("R: %s%s%s\n", strPink.c_str(), text.c_str(), strNoColor.c_str());
        }
    }

    if (subject == "PW") {
        if (this->m_debugPhysicsWorld) {
            printf("PW: %s%s%s\n", strPink.c_str(), text.c_str(), strNoColor.c_str());
        }
    }

}


Debugger debugger;
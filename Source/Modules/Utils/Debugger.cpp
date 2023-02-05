#include "Debugger.h"

Debugger::Debugger() {
    this->m_debugRenderer = false;
    this->m_debugRendererManager = false;
    this->m_displayBoundingSpheres = true;
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


bool Debugger::debugRenderer() {
    return(this->m_debugRenderer);
}

bool Debugger::debugRendererManager() {
    return(this->m_debugRendererManager);
}

bool Debugger::displayBoundingSpheres() {
    return(this->m_displayBoundingSpheres);
}


Debugger* Debugger::printRM(std::string text) {
    if (this->m_debugRendererManager) {
        printf("%s%s%s\n", strPink.c_str(), text.c_str(), strNoColor.c_str());
    }
}


Debugger debugger;
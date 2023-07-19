#ifndef __ENGINE__
#define __ENGINE__

#include <map>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "../View/Renderer/RendererManager.h"
#include "../Model/Physics/PhysicsWorld.h"

class Engine {
    public:
        Engine();

        void update(RendererManager, PhysicsWorld);
        void link(std::string, std::string);

    private:
        std::map<std::string, std::string> m_associations;
};



#endif
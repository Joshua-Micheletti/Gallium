#ifndef __ENGINE__
#define __ENGINE__

#include <map>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "../View/renderer/rendererManager.h"
#include "../Model/physics/physicsWorld.h"

class Engine {
    public:
        Engine();

        void update(RendererManager, PhysicsWorld);
        void link(std::string, std::string);

    private:
        std::map<std::string, std::string> associations_;
};



#endif
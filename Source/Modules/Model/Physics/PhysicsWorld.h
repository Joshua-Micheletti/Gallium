#ifndef __PHYSICSWORLD__
#define __PHYSICSWORLD__

#include <map>
#include <string>
#include <vector>
#include <stdio.h>

#include <glm/glm.hpp>

#include "./PhysicsBody/PhysicsBody.h"

class PhysicsWorld {
    public:
        PhysicsWorld();

        void step(float);

        PhysicsBody* physicsBody(std::string);
        std::string physicsBody(PhysicsBody*);
        PhysicsBody* newPhysicsBody(std::string);

    private:
        std::map<std::string, PhysicsBody*> m_physicsBodyBuffer;
        glm::vec3 m_gravity;
};

#endif
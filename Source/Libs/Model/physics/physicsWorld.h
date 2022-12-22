#ifndef __PHYSICSWORLD__
#define __PHYSICSWORLD__

#include <map>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <stdio.h>

#include "./physicsBody/physicsBody.h"

class PhysicsWorld {
    public:
        PhysicsWorld();

        void step(float);

        PhysicsBody* physicsBody(std::string);
        std::string physicsBody(PhysicsBody*);
        PhysicsBody* newPhysicsBody(std::string);

    private:
        std::map<std::string, PhysicsBody*> physicsBodyBuffer_;
        glm::vec3 gravity_;
};

#endif
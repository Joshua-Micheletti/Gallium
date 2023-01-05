#ifndef __PHYSICSWORLD__
#define __PHYSICSWORLD__

#define BT_USE_DOUBLE_PRECISION 1

#include <map>
#include <string>
#include <vector>
#include <stdio.h>

#include <glm/glm.hpp>
#include "btBulletDynamicsCommon.h"
#include "GLFW/glfw3.h"

#include "./PhysicsBody/PhysicsBody.h"

class PhysicsWorld {
    public:
        PhysicsWorld();

        void step();

        PhysicsBody* physicsBody(std::string);
        std::string physicsBody(PhysicsBody*);
        PhysicsBody* newPhysicsBody(std::string);

        double physicsTime();

        // REMOVE
        void updateBodies();

    private:
        btDynamicsWorld* m_world;
        btDispatcher* m_dispatcher;
        btBroadphaseInterface* m_broadphase;
        btConstraintSolver* m_solver;
        btCollisionConfiguration* m_collisionConfig;

        std::map<std::string, PhysicsBody*> m_physicsBodyBuffer;
        glm::vec3 m_gravity;

        double m_time;
        double m_tick;

        double m_physicsTime;
};

#endif
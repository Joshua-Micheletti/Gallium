#include "PhysicsWorld.h"

// MOVE TO UTILS.CPP
template<typename TK, typename TV>
std::vector<TV> extractValues(std::map<TK, TV> const& input_map) {
    std::vector<TV> retval;
    for (auto const& element : input_map) {
        retval.push_back(element.second);
    }
    return retval;
}
// MOVE TO UTILS.CPP
template<typename TK, typename TV>
std::vector<TK> extractKeys(std::map<TK, TV> const& input_map) {
    std::vector<TK> retval;
    for (auto const& element : input_map) {
        retval.push_back(element.first);
    }
    return retval;
}


PhysicsWorld::PhysicsWorld() {
    Timer PWSetupTimer;

    this->m_time = glfwGetTime();
    this->m_tick = (double)(1.0 / 30.0);

    this->m_update = true;

    this->m_gravity = glm::vec3(0, -1.0f, 0);
    // default config for the physics algorithm
    this->m_collisionConfig = new btDefaultCollisionConfiguration();
    // default collision dispatcher
    this->m_dispatcher = new btCollisionDispatcher(this->m_collisionConfig);
    // dbvt algorithm
    this->m_broadphase = new btDbvtBroadphase();
    // collision solver
    this->m_solver = new btSequentialImpulseConstraintSolver();
    // world initialization
    this->m_world = new btDiscreteDynamicsWorld(this->m_dispatcher, this->m_broadphase, this->m_solver, this->m_collisionConfig);
    // set the gravity
    this->m_world->setGravity(btVector3(0, -9.81f, 0));

    printf("\n%sSetup physics world%s\n", strGreen.c_str(), strNoColor.c_str());
    PWSetupTimer.print();
}

void PhysicsWorld::step() {
    while (this->m_time + this->m_tick < glfwGetTime()) {
        this->m_physicsTime = glfwGetTime();
        this->m_world->stepSimulation(this->m_tick);
        this->m_physicsTime = glfwGetTime() - this->m_physicsTime;
        this->m_time += this->m_tick;
    }
}


PhysicsBody* PhysicsWorld::physicsBody(std::string name) {
    if (this->m_physicsBodyBuffer.find(name) != this->m_physicsBodyBuffer.end()) {
        return(this->m_physicsBodyBuffer[name]);
    } else {
        return(NULL);
    }
}
std::string PhysicsWorld::physicsBody(PhysicsBody *pb) {
    for (auto it = this->m_physicsBodyBuffer.begin(); it != this->m_physicsBodyBuffer.end(); it++) {
        if (it->second == pb) {
            return(it->first);
        }
    }

    return("");
}
PhysicsBody* PhysicsWorld::newPhysicsBody(std::string name) {
    PhysicsBody* pb = new PhysicsBody();
    this->m_physicsBodyBuffer[name] = pb;
    this->m_world->addRigidBody(this->m_physicsBodyBuffer[name]->body());
    return(this->m_physicsBodyBuffer[name]);
}

// REMOVE
void PhysicsWorld::updateBodies() {
    for (int i = m_world->getNumCollisionObjects() - 1; i >= 0; i--) {
            btCollisionObject* obj = m_world->getCollisionObjectArray()[i];
            m_world->removeCollisionObject(obj);
            delete obj;
    }

    for (auto it = this->m_physicsBodyBuffer.begin(); it != this->m_physicsBodyBuffer.end(); it++) {
        this->m_world->addRigidBody(it->second->body());
    }
}


double PhysicsWorld::physicsTime() {
    return(this->m_physicsTime);
}
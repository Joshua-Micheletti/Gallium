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
    this->m_time = glfwGetTime();
    this->m_tick = (double)(1.0 / 60.0);

    this->m_gravity = glm::vec3(0, -1.0f, 0);
    printf("setting up physics world\n");
    // default config for the physics algorithm
    this->m_collisionConfig = new btDefaultCollisionConfiguration();
    printf("setup collision config\n");
    // default collision dispatcher
    this->m_dispatcher = new btCollisionDispatcher(this->m_collisionConfig);
    printf("setup dispatcher\n");
    // dbvt algorithm
    this->m_broadphase = new btDbvtBroadphase();
    printf("setup broadphase\n");
    // collision solver
    this->m_solver = new btSequentialImpulseConstraintSolver();
    printf("setup solver\n");
    // world initialization
    this->m_world = new btDiscreteDynamicsWorld(this->m_dispatcher, this->m_broadphase, this->m_solver, this->m_collisionConfig);
    printf("setup world\n");
    // set the gravity
    this->m_world->setGravity(btVector3(0, -9.81f, 0));
    printf("Setup Physics World\n");
}

void PhysicsWorld::step() {
    while (this->m_time + this->m_tick < glfwGetTime()) {
        this->m_world->stepSimulation(this->m_tick);
        this->m_time += this->m_tick;
    }
}

/*
void PhysicsWorld::step(float dt) {
    std::vector<PhysicsBody*> bodies = extractValues(this->m_physicsBodyBuffer);

    for (int i = 0; i < bodies.size(); i++) {
        // F = m * a
        bodies[i]->force(bodies[i]->force() + this->m_gravity * bodies[i]->mass());
        // v = v0 + F/m * t
        bodies[i]->velocity(bodies[i]->velocity() + (bodies[i]->force() / bodies[i]->mass()) * dt);
        // (xyz) = x0 + v * t
        bodies[i]->position(bodies[i]->position() + bodies[i]->velocity() * dt);

        bodies[i]->force(glm::vec3(0));
    }
}
*/


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
PhysicsBody* PhysicsWorld::newPhysicsBody(std::string name, std::string shape) {
    PhysicsBody* pb = new PhysicsBody(shape);
    this->m_physicsBodyBuffer[name] = pb;
    this->m_world->addRigidBody(this->m_physicsBodyBuffer[name]->body());
    return(this->m_physicsBodyBuffer[name]);
}
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
    this->m_gravity = glm::vec3(0, -9.81f, 0);
}

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
    return(this->m_physicsBodyBuffer[name]);
}
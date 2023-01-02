#include "PhysicsBody.h"

PhysicsBody::PhysicsBody() {
    this->m_position = glm::vec3(0);
    this->m_velocity = glm::vec3(0);
    this->m_force = glm::vec3(0);
    this->m_mass = 10.0f;
}


glm::vec3 PhysicsBody::position() {
    return(this->m_position);
}
PhysicsBody* PhysicsBody::position(glm::vec3 newPosition) {
    this->m_position = newPosition;
    return(this);
}

glm::vec3 PhysicsBody::velocity() {
    return(this->m_velocity);
}
PhysicsBody* PhysicsBody::velocity(glm::vec3 newVelocity) {
    this->m_velocity = newVelocity;
    return(this);
}

glm::vec3 PhysicsBody::force() {
    return(this->m_force);
}
PhysicsBody* PhysicsBody::force(glm::vec3 newForce) {
    this->m_force = newForce;
    return(this);
}

float PhysicsBody::mass() {
    return(this->m_mass);
}
PhysicsBody* PhysicsBody::mass(float newMass) {
    this->m_mass = newMass;
    return(this);
}
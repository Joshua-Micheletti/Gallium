#include "physicsBody.h"

PhysicsBody::PhysicsBody() {
    this->position_ = glm::vec3(0);
    this->velocity_ = glm::vec3(0);
    this->force_ = glm::vec3(0);
    this->mass_ = 10.0f;
}


glm::vec3 PhysicsBody::position() {
    return(this->position_);
}
PhysicsBody* PhysicsBody::position(glm::vec3 newPosition) {
    this->position_ = newPosition;
}

glm::vec3 PhysicsBody::velocity() {
    return(this->velocity_);
}
PhysicsBody* PhysicsBody::velocity(glm::vec3 newVelocity) {
    this->velocity_ = newVelocity;
}

glm::vec3 PhysicsBody::force() {
    return(this->force_);
}
PhysicsBody* PhysicsBody::force(glm::vec3 newForce) {
    this->force_ = newForce;
}

float PhysicsBody::mass() {
    return(this->mass_);
}
PhysicsBody* PhysicsBody::mass(float newMass) {
    this->mass_ = newMass;
}
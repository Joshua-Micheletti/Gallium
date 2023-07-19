#include "PhysicsBody.h"

PhysicsBody::PhysicsBody() {
    this->m_position = glm::vec3(0);
    this->m_velocity = glm::vec3(0);
    this->m_force = glm::vec3(0);
    this->m_mass = 1.0f;

    btTransform t;
    t.setIdentity();
    t.setOrigin(btVector3(0, 1, 0));

    btBoxShape* box = new btBoxShape(btVector3(1.0 / 2.0, 1.0 / 2.0, 1.0 / 2.0));
    btVector3 inertia(0, 0, 0);
    box->calculateLocalInertia(btScalar(this->m_mass), inertia);

    this->m_motion = new btDefaultMotionState(t);
    btRigidBody::btRigidBodyConstructionInfo info(this->m_mass, this->m_motion, box, inertia); // mass = 10
    this->m_body = new btRigidBody(info);
    this->m_body->setFriction(0.3);
    this->m_body->setSpinningFriction(0.4);
}


void PhysicsBody::box(float mass, float x, float y, float z, float width, float height, float depth, float friction, float spinningFriction) {
    this->m_mass = mass;

    btTransform t;
    t.setIdentity();
    t.setOrigin(btVector3(x, y, z));

    btBoxShape* box = new btBoxShape(btVector3(width / 2.0, height / 2.0, depth / 2.0));
    btVector3 inertia(0, 0, 0);
    box->calculateLocalInertia(btScalar(this->m_mass), inertia);

    this->m_motion = new btDefaultMotionState(t);
    btRigidBody::btRigidBodyConstructionInfo info(this->m_mass, this->m_motion, box, inertia);
    this->m_body = new btRigidBody(info);
    this->m_body->setFriction(btScalar(friction));
    this->m_body->setSpinningFriction(btScalar(spinningFriction));
}

void PhysicsBody::sphere(float mass, float x, float y, float z, float radius, float friction, float spinningFriction, float rollingFriction) {
    this->m_mass = mass;

    btTransform t;
    t.setIdentity();
    t.setOrigin(btVector3(x, y, z));

    btSphereShape* sphere = new btSphereShape(radius);
    btVector3 inertia(0, 0, 0);
    sphere->calculateLocalInertia(btScalar(this->m_mass), inertia);

    this->m_motion = new btDefaultMotionState(t);
    btRigidBody::btRigidBodyConstructionInfo info(this->m_mass, this->m_motion, sphere, inertia);
    this->m_body = new btRigidBody(info);
    this->m_body->setFriction(btScalar(friction));
    this->m_body->setSpinningFriction(btScalar(spinningFriction));
    this->m_body->setRollingFriction(btScalar(rollingFriction));
}

void PhysicsBody::plane(float x, float y, float z, float orientationX, float orientationY, float orientationZ, float friction, float spinningFriction, float rollingFriction) {
    btTransform t;
    t.setIdentity();
    t.setOrigin(btVector3(x, y, z));

    btStaticPlaneShape* plane = new btStaticPlaneShape(btVector3(orientationX, orientationY, orientationZ), btScalar(0));
    this->m_motion = new btDefaultMotionState(t);

    btRigidBody::btRigidBodyConstructionInfo info(0.0, this->m_motion, plane);
    this->m_body = new btRigidBody(info);
    this->m_body->setFriction(btScalar(friction));
    this->m_body->setRollingFriction(btScalar(rollingFriction));
    this->m_body->setSpinningFriction(btScalar(spinningFriction));
}

glm::vec3 PhysicsBody::position() {
    btVector3 currentPosition = this->m_body->getWorldTransform().getOrigin();
    return(glm::vec3((float)currentPosition.x(), (float)currentPosition.y(), (float)currentPosition.z()));
}
PhysicsBody* PhysicsBody::position(glm::vec3 newPosition) {
    this->m_position = newPosition;

    btTransform initialTransform;

    initialTransform.setOrigin(btVector3(btScalar(newPosition.x), btScalar(newPosition.y), btScalar(newPosition.z)));

    this->m_body->setWorldTransform(initialTransform);
    this->m_motion->setWorldTransform(initialTransform);

    return(this);
}

glm::vec3 PhysicsBody::rotation() {
    btScalar z;
    btScalar y;
    btScalar x;

    this->m_body->getWorldTransform().getRotation().getEulerZYX(z, y, x);
    
    return(glm::vec3((float)x, (float)y, (float)z));
}

PhysicsBody* PhysicsBody::transformMatrix(float *tmp) {
    btScalar m[16];

    this->m_body->getWorldTransform().getOpenGLMatrix(m);

    for (int i = 0; i < 16; i++) {
        tmp[i] = (float)m[i];
    }

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

btRigidBody* PhysicsBody::body() {
    return(this->m_body);
}
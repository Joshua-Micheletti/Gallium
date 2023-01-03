#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(std::string shape) {
    this->m_position = glm::vec3(0);
    this->m_velocity = glm::vec3(0);
    this->m_force = glm::vec3(0);
    this->m_mass = 1.0f;

    if (shape == "plane") {
        // create a plane
        btTransform t;
        t.setIdentity();
        t.setOrigin(btVector3(0, 0, 0));

        btStaticPlaneShape* plane = new btStaticPlaneShape(btVector3(0, 1, 0), btScalar(0));
        this->m_motion = new btDefaultMotionState(t);

        btRigidBody::btRigidBodyConstructionInfo info(0.0, this->m_motion, plane);
        this->m_body = new btRigidBody(info);
        this->m_body->setFriction(0.3);
        this->m_body->setRollingFriction(0.5);
    }

    if (shape == "sphere") {
        srand (clock());
        printf("create a sphere!\n");
        // create a sphere
        btTransform t;
        t.setIdentity();

        float x = (float)(rand() % 1000) / 100 - 5;
        float y = (float)(rand() % 3000) / 100 + 1;
        float z = (float)(rand() % 1000) / 100 - 5;

        t.setOrigin(btVector3(x, y, z));

        btSphereShape* sphere = new btSphereShape(1); // radius = 10
        btVector3 inertia(0, 0, 0);
        sphere->calculateLocalInertia(btScalar(10), inertia);

        this->m_motion = new btDefaultMotionState(t);
        btRigidBody::btRigidBodyConstructionInfo info(10, this->m_motion, sphere, inertia); // mass = 10
        this->m_body = new btRigidBody(info);
        this->m_body->setFriction(0.3);
        this->m_body->setRollingFriction(0.4);
    }

    if (shape == "cube") {
        srand (clock());
        printf("create a box!\n");
        // create a sphere
        btTransform t;
        t.setIdentity();

        float x = (float)(rand() % 1000) / 100 - 5;
        float y = (float)(rand() % 3000) / 100 + 1;
        float z = (float)(rand() % 1000) / 100 - 5;

        t.setOrigin(btVector3(x, y, z));

        btBoxShape* box = new btBoxShape(btVector3(1.0 / 2.0, 1.0 / 2.0, 1.0 / 2.0)); // radius = 10
        btVector3 inertia(0, 0, 0);
        box->calculateLocalInertia(btScalar(10), inertia);

        this->m_motion = new btDefaultMotionState(t);
        btRigidBody::btRigidBodyConstructionInfo info(10, this->m_motion, box, inertia); // mass = 10
        this->m_body = new btRigidBody(info);
        this->m_body->setFriction(0.3);
        this->m_body->setRollingFriction(0.4);
    }
}


glm::vec3 PhysicsBody::position() {
    btVector3 currentPosition = this->m_body->getWorldTransform().getOrigin();
    return(glm::vec3((float)currentPosition.x(), (float)currentPosition.y(), (float)currentPosition.z()));
}
PhysicsBody* PhysicsBody::position(glm::vec3 newPosition) {
    this->m_position = newPosition;
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
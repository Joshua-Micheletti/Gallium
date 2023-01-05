#ifndef __PHYSICSBODY__
#define __PHYSICSBODY__

#define BT_USE_DOUBLE_PRECISION 0

#include <string>
#include <stdlib.h>
#include <time.h>

#include <glm/glm.hpp>
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionShapes/btStaticPlaneShape.h"



class PhysicsBody {
    public:
        PhysicsBody();

        glm::vec3 position();
        PhysicsBody* position(glm::vec3);

        glm::vec3 rotation();
        PhysicsBody* rotation(glm::vec3);

        PhysicsBody* transformMatrix(float *);

        glm::vec3 velocity();
        PhysicsBody* velocity(glm::vec3);

        glm::vec3 force();
        PhysicsBody* force(glm::vec3);

        float mass();
        PhysicsBody* mass(float);

        btRigidBody* body();

        void box(float mass = 1, float x = 0, float y = 1, float z = 0, float width = 1, float height = 1, float depth = 1, float friction = 0.1, float spinningFriction = 0.1);
        void sphere(float mass = 1, float x = 0, float y = 1, float z = 0, float radius = 1, float friction = 0.1, float spinningFriction = 0.1, float rollingFriction = 0.1);
        void plane(float x = 0, float y = 0, float z = 0, float orientationX = 0, float orientationY = 1, float orientationZ = 0, float friction = 0.1, float spinningFriction = 0.1, float rollingFriction = 0.1);

    private:
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_velocity;
        glm::vec3 m_force;
        float m_mass;

        btRigidBody* m_body;
        btMotionState* m_motion;
};





#endif
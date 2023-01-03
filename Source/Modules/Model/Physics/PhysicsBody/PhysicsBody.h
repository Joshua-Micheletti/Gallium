#ifndef __PHYSICSBODY__
#define __PHYSICSBODY__

#define BT_USE_DOUBLE_PRECISION 1

#include <string>
#include <stdlib.h>
#include <time.h>

#include <glm/glm.hpp>
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionShapes/btStaticPlaneShape.h"



class PhysicsBody {
    public:
        PhysicsBody(std::string);

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

    private:
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_velocity;
        glm::vec3 m_force;
        float m_mass;

        btRigidBody* m_body;
        //btCollisionShape* m_shape;
        btMotionState* m_motion;
};





#endif
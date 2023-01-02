#ifndef __PHYSICSBODY__
#define __PHYSICSBODY__

#include <glm/glm.hpp>

class PhysicsBody {
    public:
        PhysicsBody();

        glm::vec3 position();
        PhysicsBody* position(glm::vec3);

        glm::vec3 velocity();
        PhysicsBody* velocity(glm::vec3);

        glm::vec3 force();
        PhysicsBody* force(glm::vec3);

        float mass();
        PhysicsBody* mass(float);

    private:
        glm::vec3 m_position;
        glm::vec3 m_velocity;
        glm::vec3 m_force;
        float m_mass;
};





#endif
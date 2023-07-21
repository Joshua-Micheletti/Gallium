#ifndef __CAMERA__
#define __CAMERA__

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Frostum.hpp"

// enumeration type to define the movement of the camera
enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// camera class
class Camera {
    public:
        // constructor method
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = 0.0f, float pitch = 0.0f);

        // position getter / setter
        Camera* position(glm::vec3);
        glm::vec3 position();

        // matrix getters
        glm::mat4 viewMatrix();
        glm::mat4 projection();
        glm::mat4 inverseViewProjectionMatrix();

        // projection setters
        Camera* projection(glm::mat4);
        Camera* projection(float, float, float, float);

        // camera vectors getters
        glm::vec3 up();
        glm::vec3 front();
        glm::vec3 right();

        // angles getters
        Camera* yaw(float);
        Camera* pitch(float);

        // movement and look processors (update the position / angle of the camera)
        void processMouseMovement(float, float, bool);
        void processMovement(CameraMovement, float);

        // frostum getter
        Frostum* frostum();

    private:
        // camera vectors
        glm::vec3 m_position;
        glm::vec3 m_up;
        glm::vec3 m_right;
        glm::vec3 m_worldUp;
        glm::vec3 m_front;

        // camera angles
        float m_yaw;
        float m_pitch;

        // movement and look parameters
        float m_movementSpeed;
        float m_sensitivity;
        float m_zoom;

        // camera matrices
        glm::mat4 m_viewMatrix;
        glm::mat4 m_projection;

        // camera frostum
        Frostum* m_frostum;

        // method for updating the camera vectors after a change
        void updateVectors();

        // frostum constructor
        void createFrustumFromCamera(float, float, float, float);
        
};

#endif
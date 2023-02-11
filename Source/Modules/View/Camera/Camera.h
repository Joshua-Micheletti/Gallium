#ifndef __CAMERA__
#define __CAMERA__

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Frostum.h"

enum CameraMovement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
  UP,
  DOWN
};

class Camera {
  public:
    Camera(glm::vec3, glm::vec3, float, float);

    void position(glm::vec3);
    void orientation(glm::vec3);
    void up(glm::vec3);

    glm::vec3 position();
    glm::vec3 orientation();
    glm::vec3 orientationCartesian();

    glm::vec3 up();
    glm::mat4 viewMatrix();

    glm::vec3 front();
    glm::vec3 right();

    void createFrustumFromCamera(float, float, float, float);
    Frostum* frostum();

    void processMouseMovement(float, float, bool);
    void processMovement(CameraMovement, float);

  private:
    glm::vec3 m_position;
    glm::vec3 m_orientation;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;
    glm::vec3 m_front;

    float m_yaw;
    float m_pitch;

    float m_movementSpeed;
    float m_sensitivity;
    float m_zoom;


    glm::mat4 m_viewMatrix;

    Frostum* m_frostum;
    
    void calculateViewMatrix();
    glm::vec3 polarToCartesian(glm::vec3);

    void updateVectors();
};

#endif
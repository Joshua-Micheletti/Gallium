#ifndef __CAMERA__
#define __CAMERA__

#include <glm/glm.hpp>

class Camera {
  public:
    Camera(glm::vec3, glm::vec3, glm::vec3);
    void setPosition(glm::vec3);
    void setOrientation(glm::vec3);
    void setUp(glm::vec3);
    glm::vec3 getPosition();
    glm::vec3 getOrientation();
    glm::vec3 getOrientationCartesian();
    glm::vec3 getUp();
    glm::mat4 getViewMatrix();
    bool mainCamera;

  private:
    glm::vec3 position;
    glm::vec3 orientation;
    glm::vec3 up;
    glm::mat4 viewMatrix;
    void calculateViewMatrix();
    glm::vec3 polarToCartesian(glm::vec3);
};

#endif
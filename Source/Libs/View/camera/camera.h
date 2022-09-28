#ifndef __CAMERA__
#define __CAMERA__

#include <glm/glm.hpp>

class Camera {
  public:
    Camera(glm::vec3, glm::vec3, glm::vec3);
    void position(glm::vec3);
    void orientation(glm::vec3);
    void up(glm::vec3);
    glm::vec3 position();
    glm::vec3 orientation();
    glm::vec3 orientationCartesian();
    glm::vec3 up();
    glm::mat4 viewMatrix();
    
    bool mainCamera;

  private:
    glm::vec3 position_;
    glm::vec3 orientation_;
    glm::vec3 up_;
    glm::mat4 viewMatrix_;
    void calculateViewMatrix();
    glm::vec3 polarToCartesian(glm::vec3);
};

#endif
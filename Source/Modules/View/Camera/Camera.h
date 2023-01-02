#ifndef __CAMERA__
#define __CAMERA__

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


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

  private:
    glm::vec3 m_position;
    glm::vec3 m_orientation;
    glm::vec3 m_up;
    glm::mat4 m_viewMatrix;
    
    void calculateViewMatrix();
    glm::vec3 polarToCartesian(glm::vec3);
};

#endif
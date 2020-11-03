#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <cmath>
#include "camera.h"
#include <SFML\Graphics.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 orientation, glm::vec3 up) {
  this->position = position;
  this->orientation = orientation;
  this->up = up;
  this->mainCamera = false;
  calculateViewMatrix();
}

void Camera::setPosition(glm::vec3 position) {
  this->position = position;
  calculateViewMatrix();
}

void Camera::setOrientation(glm::vec3 orientation) {
  this->orientation = orientation;
  if (this->mainCamera == true) {
    if (this->orientation.z > 89.0f) {
      this->orientation.z = 89.0f;
    }

    if (this->orientation.z < -89.0f) {
      this->orientation.z = -89.0f;
    }
  }
  calculateViewMatrix();
}

void Camera::setUp(glm::vec3 up) {
  this->up = up;
  calculateViewMatrix();
}

glm::vec3 Camera::getPosition() {
  return(this->position);
}

glm::vec3 Camera::getOrientation() {
  return(this->orientation);
}

glm::vec3 Camera::getOrientationCartesian() {
  return(polarToCartesian(this->orientation));
}

glm::vec3 Camera::getUp() {
  return(this->up);
}

glm::mat4 Camera::getViewMatrix() {
  return(this->viewMatrix);
}

void Camera::calculateViewMatrix() {
  this->viewMatrix = glm::lookAt(this->position, polarToCartesian(this->orientation) + this->position, this->up);
}

glm::vec3 Camera::polarToCartesian(glm::vec3 polar) {
  return(glm::normalize(glm::vec3(cos(glm::radians(polar.y)) * cos(glm::radians(polar.z)),
  sin(glm::radians(polar.z)),
  sin(glm::radians(polar.y)) * cos(glm::radians(polar.z)))));
}

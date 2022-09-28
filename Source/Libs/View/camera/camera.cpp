#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 orientation, glm::vec3 up) {
  this->position_ = position;
  this->orientation_ = orientation;
  this->up_ = up;
  this->mainCamera = false;
  calculateViewMatrix();
}

void Camera::position(glm::vec3 position) {
  this->position_ = position;
  calculateViewMatrix();
}

void Camera::orientation(glm::vec3 orientation) {
  this->orientation_ = orientation;
  if (this->mainCamera == true) {
    if (this->orientation_.z > 89.0f) {
      this->orientation_.z = 89.0f;
    }

    if (this->orientation_.z < -89.0f) {
      this->orientation_.z = -89.0f;
    }
  }
  calculateViewMatrix();
}

void Camera::up(glm::vec3 up) {
  this->up_ = up;
  calculateViewMatrix();
}

glm::vec3 Camera::position() {
  return(this->position_);
}

glm::vec3 Camera::orientation() {
  return(this->orientation_);
}

glm::vec3 Camera::orientationCartesian() {
  return(this->polarToCartesian(this->orientation_));
}

glm::vec3 Camera::up() {
  return(this->up_);
}

glm::mat4 Camera::viewMatrix() {
  return(this->viewMatrix_);
}

void Camera::calculateViewMatrix() {
  this->viewMatrix_ = glm::lookAt(this->position_, this->polarToCartesian(this->orientation_) + this->position_, this->up_);
}

glm::vec3 Camera::polarToCartesian(glm::vec3 polar) {
  return(glm::normalize(glm::vec3(cos(glm::radians(polar.y)) * cos(glm::radians(polar.z)),
  sin(glm::radians(polar.z)),
  sin(glm::radians(polar.y)) * cos(glm::radians(polar.z)))));
}

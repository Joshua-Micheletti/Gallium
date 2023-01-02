#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 orientation, glm::vec3 up) {
  this->m_position = position;
  this->m_orientation = orientation;
  this->m_up = up;
  calculateViewMatrix();
}

void Camera::position(glm::vec3 position) {
  this->m_position = position;
  calculateViewMatrix();
}

void Camera::orientation(glm::vec3 orientation) {
  this->m_orientation = orientation;
  if (this->m_orientation.z > 89.0f) {
    this->m_orientation.z = 89.0f;
  }

  if (this->m_orientation.z < -89.0f) {
    this->m_orientation.z = -89.0f;
  }
  calculateViewMatrix();
}

void Camera::up(glm::vec3 up) {
  this->m_up = up;
  calculateViewMatrix();
}

glm::vec3 Camera::position() {
  return(this->m_position);
}

glm::vec3 Camera::orientation() {
  return(this->m_orientation);
}

glm::vec3 Camera::orientationCartesian() {
  return(this->polarToCartesian(this->m_orientation));
}

glm::vec3 Camera::up() {
  return(this->m_up);
}

glm::mat4 Camera::viewMatrix() {
  return(this->m_viewMatrix);
}

void Camera::calculateViewMatrix() {
  this->m_viewMatrix = glm::lookAt(this->m_position, this->polarToCartesian(this->m_orientation) + this->m_position, this->m_up);
}

glm::vec3 Camera::polarToCartesian(glm::vec3 polar) {
  return(glm::normalize(glm::vec3(cos(glm::radians(polar.y)) * cos(glm::radians(polar.z)),
  sin(glm::radians(polar.z)),
  sin(glm::radians(polar.y)) * cos(glm::radians(polar.z)))));
}

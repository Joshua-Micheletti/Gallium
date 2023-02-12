#include "Camera.h"


Camera::Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = 0.0f, float pitch = 0.0f) {
  this->m_position = position;
  this->m_worldUp = up;

  this->m_yaw = yaw;
  this->m_pitch = pitch;

  this->updateVectors();

  this->m_projection = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 10000.0f);

  this->m_sensitivity = 0.08f;

  this->m_frostum = new Frostum();
}

Camera* Camera::position(glm::vec3 position) {
  this->m_position = position;
  return(this);
}

glm::vec3 Camera::position() {
  return(this->m_position);
}

glm::vec3 Camera::up() {
  return(this->m_up);
}

glm::mat4 Camera::viewMatrix() {
  return(glm::lookAt(this->m_position, this->m_position + this->m_front, this->m_up));
}

glm::mat4 Camera::projection() {
  return(this->m_projection);
}
Camera* Camera::projection(glm::mat4 p) {
  this->m_projection = p;
  return(this);
}
Camera* Camera::projection(float fov, float aspect, float nearZ, float farZ) {
  this->m_projection = glm::perspective(glm::radians(fov), aspect, nearZ, farZ);
  return(this);
}

glm::vec3 Camera::front() {
  return(this->m_front);
}

glm::vec3 Camera::right() {
  return(this->m_right);
}

glm::vec3 Camera::polarToCartesian(glm::vec3 polar) {
  return(glm::normalize(glm::vec3(cos(glm::radians(polar.y)) * cos(glm::radians(polar.z)),
  sin(glm::radians(polar.z)),
  sin(glm::radians(polar.y)) * cos(glm::radians(polar.z)))));
}


void Camera::createFrustumFromCamera(float aspect, float fovY, float zNear, float zFar) {
    const float halfVSide = zFar * tanf(fovY * .5f);
    const float halfHSide = halfVSide * aspect;
    const glm::vec3 frontMultFar = zFar * this->front();

    this->m_frostum->nearPlane({ this->position() + zNear * this->front(), this->front() });
    this->m_frostum->farPlane({ this->position() + frontMultFar, -this->front() });
    this->m_frostum->right({ this->position(),
                            glm::cross(frontMultFar - this->right() * halfHSide, this->up()) });
    this->m_frostum->left({ this->position(),
                            glm::cross(this->up(),frontMultFar + this->right() * halfHSide) });
    this->m_frostum->top({ this->position(),
                            glm::cross(this->right(), frontMultFar - this->up() * halfVSide) });
    this->m_frostum->bottom({ this->position(),
                            glm::cross(frontMultFar + this->up() * halfVSide, this->right()) });
}

Frostum* Camera::frostum() {
  this->createFrustumFromCamera(16.0f / 9.0f, 45.0f, 0.1, 10000.0);
  return(this->m_frostum);
}

void Camera::updateVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
    front.y = sin(glm::radians(this->m_pitch));
    front.z = sin(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
    this->m_front = glm::normalize(front);

    this->m_right = glm::normalize(glm::cross(this->m_front, this->m_worldUp));
    this->m_up = glm::normalize(glm::cross(this->m_right, this->m_front));

    // this->createFrustumFromCamera(16.0f / 9.0f, 45.0f, 0.1, 10000.0);
}


Camera* Camera::yaw(float yaw) {
  this->m_yaw = yaw;
  this->updateVectors();
  return(this);
}

Camera* Camera::pitch(float pitch) {
  this->m_pitch = pitch;
  this->updateVectors();
  return(this);
}

void Camera::processMovement(CameraMovement direction, float distance) {
  if (direction == FORWARD) {
    this->m_position += this->m_front * distance;
  }
  if (direction == BACKWARD) {
    this->m_position -= this->m_front * distance;
  }
  if (direction == LEFT) {
    this->m_position -= this->m_right * distance;
  }
  if (direction == RIGHT) {
    this->m_position += this->m_right * distance;
  }
  if (direction == UP) {
    this->m_position += this->m_up * distance;
  }
  if (direction == DOWN) {
    this->m_position -= this->m_up * distance;
  }
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) {
  xoffset *= this->m_sensitivity;
  yoffset *= this->m_sensitivity;

  this->m_yaw += xoffset;
  this->m_pitch += yoffset;

  if (constrainPitch) {
    if (this->m_pitch > 89.0f) {
      this->m_pitch = 89.0f;
    }
    if (this->m_pitch < -89.0f) {
      this->m_pitch = -89.0f;
    }
  }

  this->updateVectors();
}
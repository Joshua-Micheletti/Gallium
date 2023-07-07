#include "Plane.h"

Plane::Plane() {
    this->m_normal = glm::vec3(0.f, 1.f, 0.f);
    this->m_distance = 0.f;
}

Plane::Plane(glm::vec3 p1, glm::vec3 norm) {
    this->m_normal = glm::normalize(norm);
    this->m_distance = glm::dot(this->m_normal, p1);
    this->m_center = p1;
    this->m_materialIndex = 0;
}


Plane* Plane::normal(glm::vec3 n) {
    this->m_normal = n;
    return(this);
}
glm::vec3 Plane::normal() {
    return(this->m_normal);
}

Plane* Plane::center(glm::vec3 c) {
    this->m_center = c;
    return(this);
}
glm::vec3 Plane::center() {
    return(this->m_center);
}

Plane* Plane::materialIndex(int m) {
    this->m_materialIndex = m;
    return(this);
}
int Plane::materialIndex() {
    return(this->m_materialIndex);
}

Plane* Plane::distance(float d) {
    this->m_distance = d;
    return(this);
}
float Plane::distance() {
    return(this->m_distance);
}


float Plane::getSignedDistanceToPlane(glm::vec3 point) {
    return(glm::dot(this->m_normal, point) - this->m_distance);
}

bool Plane::isOnForwardPlane(glm::vec3 center, float radius) {
    return(this->getSignedDistanceToPlane(center) > -radius);
}
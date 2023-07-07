#include "Sphere.hpp"

Sphere::Sphere() {
    this->m_center = glm::vec3(0.0);
    this->m_radius = 1.0;
    this->m_materialIndex = 0;
}

Sphere::Sphere(glm::vec3 center, float radius) {
    this->m_center = center;
    this->m_radius = radius;
    this->m_materialIndex = 0;
}

Sphere::Sphere(glm::vec3 center, float radius, int materialIndex) {
    this->m_center = center;
    this->m_radius = radius;
    this->m_materialIndex = 0;
}


glm::vec3 Sphere::center() {
    return(this->m_center);
}
Sphere* Sphere::center(glm::vec3 c) {
    this->m_center = c;
    return(this);
}

float Sphere::radius() {
    return(this->m_radius);
}
Sphere* Sphere::radius(float r) {
    this->m_radius = r;
    return(this);
}

int Sphere::materialIndex() {
    return(this->m_materialIndex);
}
Sphere* Sphere::materialIndex(int m) {
    this->m_materialIndex = m;
    return(this);
}
    
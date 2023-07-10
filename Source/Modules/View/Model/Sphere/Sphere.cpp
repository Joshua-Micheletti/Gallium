#include "Sphere.hpp"

Sphere::Sphere() {
    this->m_center = glm::vec3(0.0);
    this->m_radius = 1.0;
    this->m_materialIndex = 0;
    this->mesh("ME_Sphere");
    this->position(this->m_center);
    this->scale(glm::vec3(this->m_radius / 2));
}

Sphere::Sphere(glm::vec3 center, float radius) {
    this->m_center = center;
    this->m_radius = radius;
    this->m_materialIndex = 0;

    this->mesh("ME_Sphere");
    this->position(this->m_center);
    this->scale(glm::vec3(this->m_radius / 2));
}

Sphere::Sphere(glm::vec3 center, float radius, int materialIndex) {
    this->m_center = center;
    this->m_radius = radius;
    this->m_materialIndex = 0;

    this->mesh("ME_Sphere");
    this->position(this->m_center);
    this->scale(glm::vec3(this->m_radius / 2));
}

Sphere* Sphere::scale(glm::vec3 s) {
    // this->Model::scale(s);
    this->m_scale = glm::vec3(std::max(std::max(s.x, s.y), s.z));
    printf("%lf, %lf, %lf\n", this->m_scale.x, this->m_scale.y, this->m_scale.z);

    this->m_scaleMatrix = glm::scale(glm::mat4(1), this->m_scale);
    // this->m_scale = s;
    this->m_modelMatrix = this->m_translationMatrix * this->m_rotationMatrix * this->m_scaleMatrix;
    return(this);
}

glm::vec3 Sphere::scale(void) {
    return(this->m_scale);
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
    
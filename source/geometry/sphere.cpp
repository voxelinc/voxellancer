#include "sphere.h"

Sphere::Sphere() {

}

Sphere::~Sphere() {

}

const glm::vec3 &Sphere::center() const {
    return m_center;
}

void Sphere::setCenter(glm::vec3 &center) {
    m_center = center;
}

float Sphere::radius() const {
    return m_radius;
}

void Sphere::setRadius(float radius) {
    m_radius = radius;
}


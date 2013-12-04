#include "sphere.h"

#include <cassert>


Sphere::Sphere():
    m_position(0.0f, 0.0f, 0.0f),
    m_radius(0.0f)
{

}

Sphere::Sphere(const glm::vec3 &position, float radius):
    m_position(position),
    m_radius(radius)
{

}

Sphere::~Sphere() {

}

float Sphere::radius() const {
    return m_radius;
}

void Sphere::setRadius(float radius) {
    assert(radius >= 0);
    m_radius = radius;
}

const glm::vec3 &Sphere::position() const {
    return m_position;
}

void Sphere::setPosition(const glm::vec3 &position) {
    m_position = position;
}

bool Sphere::intersects(const Sphere &other) const {
    glm::vec3 delta = other.m_position - m_position;
    return glm::length(delta) < other.m_radius + m_radius;
}

bool Sphere::contains(const Sphere &other) const {
    glm::vec3 delta = other.m_position - m_position;
    return glm::length(delta) + other.m_radius < m_radius;
}

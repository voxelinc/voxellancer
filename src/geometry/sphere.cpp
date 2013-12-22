#include "sphere.h"

#include <cassert>

#include "geometry/aabb.h"


Sphere::Sphere():
    m_position(0.0f, 0.0f, 0.0f),
    m_radius(0.0f)
{

}

Sphere::Sphere(const glm::vec3 &position, float radius):
    m_position(position),
    m_radius(radius)
{
    assert(radius >= 0 && std::isfinite(radius));
    assert(std::isfinite(position.x) && std::isfinite(position.y) && std::isfinite(position.z));
}

Sphere::~Sphere() {

}

float Sphere::radius() const {
    return m_radius;
}

void Sphere::setRadius(float radius) {
    assert(radius >= 0 && std::isfinite(radius));
    assert(std::isfinite(radius));
    m_radius = radius;
}

const glm::vec3 &Sphere::position() const {
    return m_position;
}

void Sphere::setPosition(const glm::vec3 &position) {
    assert(std::isfinite(position.x) && std::isfinite(position.x) && std::isfinite(position.x));
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

Sphere Sphere::applied(const WorldTransform& transform) const {
    return Sphere(transform.applyTo(m_position), m_radius * transform.scale());
}

Sphere Sphere::inverseApplied(const WorldTransform& transform) const {
    return Sphere(transform.inverseApplyTo(m_position), m_radius / transform.scale());
}


#include "sphere.h"

#include <cassert>

#include "utils/glmisfinite.h"

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
    assert(std::isfinite(position));
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
    assert(std::isfinite(position));
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

bool Sphere::nearTo(const TAABB<int>& aabb) const {
    Sphere aabbSphere = Sphere::containing(aabb);
    return intersects(aabbSphere);
}

bool Sphere::containedBy(const TAABB<int>& aabb) const {
    return
        m_position.x - m_radius >= aabb.llf().x &&
        m_position.y - m_radius >= aabb.llf().y &&
        m_position.z - m_radius >= aabb.llf().z &&
        m_position.x + m_radius <= aabb.rub().x &&
        m_position.y + m_radius <= aabb.rub().y &&
        m_position.z + m_radius <= aabb.rub().z;
}



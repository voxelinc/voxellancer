#include "ray.h"

#include <cmath>

#include "sphere.h"


Ray::Ray(const glm::vec3& origin, const glm::vec3& direction):
    m_origin(origin),
    m_direction(direction)
{
    assert(glm::length(direction) != 0);
}

const glm::vec3& Ray::origin() const{
    return m_origin;
}

void Ray::setOrigin(const glm::vec3& origin) {
    m_origin = origin;
}

const glm::vec3& Ray::direction() const {
    return m_direction;
}

void Ray::setDirection(const glm::vec3& direction) {
    assert(glm::length(direction) != 0);
    m_direction;
}

bool Ray::intersects(const Sphere& sphere) const {
    glm::vec3 o = m_origin - sphere.position();

    float a = glm::dot(m_direction, m_direction);
    float b = 2 * glm::dot(m_direction, o);
    float c = glm::dot(o, o) - (sphere.radius() * sphere.radius());

    float t0 = (-b - std::sqrt(b*b - 4*a*c)) / (2*a);
    float t1 = (-b + std::sqrt(b*b - 4*a*c)) / (2*a);

    return t0 >= 0 || t1 >= 0;
}

Ray Ray::applied(const WorldTransform& transform) const {
    return Ray(transform.applyTo(m_origin), transform.applyTo(m_direction));
}

Ray Ray::inverseApplied(const WorldTransform& transform) const {
    return Ray(transform.inverseApplyTo(m_origin), transform.inverseApplyTo(m_direction));
}


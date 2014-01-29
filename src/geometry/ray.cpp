#include "ray.h"

#include <cmath>
#include <iostream>

#include "geometry/transform.h"

#include "utils/tostring.h"

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
    m_direction = direction;
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

bool Ray::nearTo(const TAABB<int>& aabb) const {
    Sphere aabbSphere = Sphere::containing(aabb);
    return intersects(aabbSphere);
}

bool Ray::containedBy(const TAABB<int>& aabb) const {
    return false;
}


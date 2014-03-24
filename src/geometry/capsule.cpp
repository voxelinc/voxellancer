#include "capsule.h"

#include "transform.h"

#include "utils/tostring.h"

#include "sphere.h"
#include "ray.h"


Capsule::Capsule() {

}

Capsule::Capsule(const glm::vec3& origin, const glm::vec3& direction, const float radius) :
    m_origin(origin),
    m_direction(direction),
    m_radius(radius)
{
}

const glm::vec3& Capsule::origin() const {
    return m_origin;
}

void Capsule::setOrigin(const glm::vec3& origin) {
    m_origin = origin;
}

const glm::vec3& Capsule::direction() const {
    return m_direction;
}

void Capsule::setDirection(const glm::vec3& direction) {
    m_direction = direction;
}


const float Capsule::radius() const {
    return m_radius;
}

void Capsule::setRadius(const float radius) {
    m_radius = radius;
}

bool Capsule::intersects(const Sphere& sphere) const {
    //http://www.gamedev.net/topic/190774-intersection-of-sphere-and-cylinder/
    float t = glm::dot(m_direction, sphere.position() - m_origin) / glm::dot(m_direction, m_direction);
    glm::vec3 closestPoint = m_origin + glm::clamp(t, 0.0f, 1.0f) * m_direction;
    glm::vec3 distance = sphere.position() - closestPoint;
    return (glm::dot(distance, distance) <= (sphere.radius() + m_radius) * (sphere.radius() + m_radius));
}

bool Capsule::nearTo(const TAABB<int>& aabb) const {
    glm::vec3 extendDirection(
        (m_direction.x < 0 ? -m_radius : m_radius),
        (m_direction.y < 0 ? -m_radius : m_radius),
        (m_direction.z < 0 ? -m_radius : m_radius));

    glm::vec3 a(m_origin - extendDirection);
    glm::vec3 b(m_origin + m_direction + extendDirection);
    glm::ivec3 llf(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
    glm::ivec3 rub(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));

    TAABB<int> lineAABB(llf, rub);
    return lineAABB.intersects(aabb);
}

bool Capsule::containedBy(const TAABB<int>& aabb) const {
    glm::vec3 extendDirection(
        (m_direction.x < 0 ? -m_radius : m_radius),
        (m_direction.y < 0 ? -m_radius : m_radius),
        (m_direction.z < 0 ? -m_radius : m_radius));

    //extend endpoints along axes
    glm::vec3 normalizedDirection = glm::normalize(m_direction);
    return aabb.contains(m_origin - extendDirection)
        && aabb.contains(m_origin + m_direction + extendDirection);
}


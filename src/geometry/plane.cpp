#include "plane.h"

#include <glow/logging.h>

#include "line.h"
#include "ray.h"


Plane::Plane() = default;

Plane::Plane(const glm::vec3& position, const glm::vec3& normal):
    m_position(position),
    m_normal(normal)
{

}

const glm::vec3& Plane::position() const {
    return m_position;
}

void Plane::setPosition(const glm::vec3& position) {
    m_position = position;
}

const glm::vec3& Plane::normal() const {
    return m_normal;
}

void Plane::setNormal(const glm::vec3& normal) {
    m_normal = normal;
}

PointIntersection Plane::intersectionWith(const Ray& ray) const {
    float dot = glm::dot(ray.direction(), m_normal);

    if (dot == 0.0f) {
        return PointIntersection();
    }

    float t = (glm::dot(m_position, m_normal) - glm::dot(ray.origin(), m_normal)) / dot;

    if (t < 0.0f) {
        return PointIntersection();
    }

    return PointIntersection(ray.origin() + t * ray.direction());
}

PointIntersection Plane::intersectionWith(const Line& line) const {
    if (line.length() == 0.0f) {
        return PointIntersection();
    }

    Ray ray(Ray::fromTo(line.a(), line.b()));
    PointIntersection intersection = intersectionWith(ray);

    if (!intersection) {
        return PointIntersection();
    }

    ray = Ray::fromTo(line.b(), line.a());

    return intersectionWith(ray);
}


#include "plane.h"

#include <glow/logging.h>

#include "line.h"
#include "ray.h"


Plane::Plane() {

}

Plane::Plane(const glm::vec3& position, const glm::vec3& normal):
    m_position(position),
    m_normal(normal)
{

}

glm::vec3 Plane::intersectionPoint(const Ray& ray, bool& intersects) const {glow::debug() << "Checking " << ray.origin() << " " << ray.direction() << " against " << m_position << "/" << m_normal;
    float dot = glm::dot(ray.direction(), m_normal);

    if (dot == 0.0f) {
        intersects = false;
        return glm::vec3();
    }

    float t = -(glm::dot(ray.origin(), m_normal) + glm::dot(m_position, m_normal)) / dot;
    glow::debug() << "T: " << t;
    if (t < 0.0f) {
        intersects = false;
        return glm::vec3();
    }
    glow::debug() << "  intersect at " << glm::vec3(ray.origin() + t * ray.direction());
    intersects = true;
    return glm::vec3(ray.origin() + t * ray.direction());
}

glm::vec3 Plane::intersectionPoint(const Line& line, bool& intersects) const {
    if (line.length() == 0.0f) {
        intersects = false;
        return glm::vec3();
    }

    Ray ray(Ray::fromTo(line.a(), line.b()));
    glm::vec3 point = intersectionPoint(ray, intersects);

    if (!intersects) {
        return glm::vec3();
    }

    ray = Ray::fromTo(line.b(), line.a());
    intersectionPoint(ray, intersects);

    return point;
}


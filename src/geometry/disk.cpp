#include "disk.h"

#include "plane.h"


Disk::Disk() = default;

Disk::Disk(const glm::vec3& position, const glm::vec3& normal, float radius):
    m_position(position),
    m_normal(normal),
    m_radius(radius)
{

}

const glm::vec3& Disk::position() const {
    return m_position;
}

void Disk::setPosition(const glm::vec3& position) {
    m_position = position;
}

const glm::vec3& Disk::normal() const {
    return m_normal;
}

void Disk::setNormal(const glm::vec3& normal) {
    m_normal = normal;
}

float Disk::radius() const {
    return m_radius;
}

void Disk::setRadius(float radius) {
    m_radius = radius;
}

PointIntersection Disk::intersectionWith(const Ray& ray) const {
    Plane plane(m_position, m_normal);

    PointIntersection intersection = plane.intersectionWith(ray);
    if (!intersection) {
        return intersection;
    }

    if (glm::length(intersection.point() - m_position) <= m_radius) {
        return intersection;
    } else {
        return PointIntersection();
    }
}

PointIntersection Disk::intersectionWith(const Line& line) const {
    Plane plane(m_position, m_normal);

    PointIntersection intersection = plane.intersectionWith(line);
    if (!intersection) {
        return intersection;
    }

    if (glm::length(intersection.point() - m_position) <= m_radius) {
        return intersection;
    } else {
        return PointIntersection();
    }
}

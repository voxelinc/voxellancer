#include "point.h"

#include "sphere.h"


Point::Point() {

}

Point::Point(const glm::vec3& pos):
    m_position(pos)
{
}

const glm::vec3& Point::position() const {
    return m_position;
}

void Point::setPosition(const glm::vec3& pos) {
    m_position = pos;
}

bool Point::intersects(const Sphere& sphere) const {
    return glm::length(sphere.position() - m_position) < sphere.radius();
}

bool Point::nearTo(const TAABB<int>& aabb) const {
    return containedBy(aabb);
}

bool Point::containedBy(const TAABB<int>& aabb) const {
    return aabb.contains(m_position);
}


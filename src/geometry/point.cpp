#include "point.h"

#include "sphere.h"
#include "aabb.h"


Point::Point():
    m_x(0.0f),
    m_y(0.0f),
    m_z(0.0f)
{

}

Point::Point(const glm::vec3& position):
    m_x(position.x),
    m_y(position.y),
    m_z(position.z)
{

}

float Point::x() const {
    return m_x;
}

void Point::setX(float x) {
    m_x = x;
}

float Point::y() const {
    return m_y;
}

void Point::setY(float y) {
    m_y = y;
}

float Point::z() const {
    return m_z;
}

void Point::setZ(float z) {
    m_z = z;
}

glm::vec3 Point::vec3() const {
    return glm::vec3(m_x, m_y, m_z);
}

bool Point::intersects(const Sphere& sphere) const {
    glm::vec3 delta = vec3() - sphere.position();
    float squaredDistance = glm::dot(delta, delta);

    return squaredDistance < sphere.radius() * sphere.radius();
}

bool Point::nearTo(const TAABB<int>& aabb) const {
    return containedBy(aabb);
}

bool Point::containedBy(const TAABB<int>& aabb) const {
    return
        m_x >= aabb.llf().x && m_x <= aabb.rub().x &&
        m_y >= aabb.llf().y && m_y <= aabb.rub().y &&
        m_z >= aabb.llf().z && m_z <= aabb.rub().z;
}


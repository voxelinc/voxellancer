#include "point.h"

#include <iostream>

#include "worldtransform.h"

#include "utils/tostring.h"

#include "sphere.h"


Point::Point() {

}

Point::Point(const glm::vec3& p):
    m_p(p)
{
}

const glm::vec3& Point::get() const {
    return m_p;
}

void Point::set(const glm::vec3& p) {
    m_p = p;
}


bool Point::intersects(const Sphere& sphere) const {
    return glm::length(sphere.position() - m_p) < sphere.radius();
}

bool Point::nearTo(const TAABB<int>& aabb) const {
    return containedBy(aabb);
}

bool Point::containedBy(const TAABB<int>& aabb) const {
    return aabb.contains(m_p);
}


#include "pointintersection.h"


PointIntersection::PointIntersection():
    Intersection(false)
{
}

PointIntersection::PointIntersection(const glm::vec3& point):
    Intersection(true),
    m_point(point)
{
}

PointIntersection::~PointIntersection() = default;

const glm::vec3& PointIntersection::point() {
    return m_point;
}

void PointIntersection::setPoint(const glm::vec3& point) {
    m_point = point;
}

PointIntersection::operator const glm::vec3&() const {
    return m_point;
}


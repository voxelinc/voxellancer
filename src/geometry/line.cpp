#include "line.h"

#include "geometry/transform.h"

#include "sphere.h"
#include "ray.h"


Line::Line() {

}

Line::Line(const glm::vec3& a, const glm::vec3& b):
    m_a(a),
    m_b(b)
{
}

const glm::vec3& Line::a() const {
    return m_a;
}

void Line::setA(const glm::vec3& a) {
    m_a = a;
}

const glm::vec3& Line::b() const {
    return m_b;
}

void Line::setB(const glm::vec3& b) {
    m_b = b;
}

bool Line::intersects(const Sphere& sphere) const {
    Ray r1(m_a, m_b - m_a);
    Ray r2(m_b, m_a - m_b);

    return r1.intersects(sphere) && r2.intersects(sphere);
}

bool Line::nearTo(const TAABB<int>& aabb) const {
    glm::ivec3 llf(std::min(m_a.x, m_b.x), std::min(m_a.y, m_b.y), std::min(m_a.z, m_b.z));
    glm::ivec3 urb(std::max(m_a.x, m_b.x), std::max(m_a.y, m_b.y), std::max(m_a.z, m_b.z));

    TAABB<int> lineAABB(llf, urb);
    return lineAABB.intersects(aabb);
}

bool Line::containedBy(const TAABB<int>& aabb) const {
    return aabb.contains(m_a) && aabb.contains(m_b);
}


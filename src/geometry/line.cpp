#include "line.h"

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
    return m_b
}

void Line::setB(const glm::vec3& b) {
    m_b = b;
}

bool Line::intersects(const Sphere& sphere) {
    Ray r1(m_a, m_b - m_a);
    Ray r2(m_b, m_a - m_b);

    return r1.intersects(sphere) && r2.intersects(sphere);
}

Line Line::applied(const WorldTransform& transform) const {
    return Line(transform.applyTo(m_a), transform.applyTo(m_b));
}

Line Line::inverseApplied(const WorldTransform& transform) const {
    return Line(transform.inverseApplyTo(m_a), transform.inverseApplyTo(m_b));
}


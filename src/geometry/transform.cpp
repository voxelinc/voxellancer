#include "geometry/transform.h"

#include <glow/logging.h>

#include "utils/glmisfinite.h"

Transform::Transform(glm::vec3 center, float scale) :
    m_position(0),
    m_orientation(),
    m_center(center),
    m_scale(scale)
{
    assert(std::isfinite(center));
}

Transform::Transform(const Transform& transform, const glm::vec3& positionDelta, const glm::quat& orientationDelta):
    Transform(transform)
{
    moveWorld(positionDelta);
    rotate(orientationDelta);
    assert(std::isfinite(m_center);
    assert(std::isfinite(m_orientation);
}

Transform::~Transform() {

}

const glm::quat& Transform::orientation() const {
    return m_orientation;
}

void Transform::setOrientation(const glm::quat& quat){
    m_orientation = quat;
    assert(std::isfinite(m_orientation));
}

const glm::vec3 &Transform::position() const {
    return m_position;
}

void Transform::setPosition(const glm::vec3& pos){
    assert(std::isfinite(pos);
    m_position = pos;
}

// move in local axis direction
void Transform::move(const glm::vec3& dist) {
    m_position += m_orientation * dist;
}

// move in world axis direction
void Transform::moveWorld(const glm::vec3& dist) {
    m_position += dist;
}

// rotate around local axis
void Transform::rotate(const glm::quat &qrot) {
    m_orientation = m_orientation * qrot;
    assert(std::isfinite(m_orientation));
}

void Transform::rotateWorld(const glm::quat &qrot) {
    m_orientation = qrot * m_orientation;
    assert(std::isfinite(m_orientation));
}

const glm::mat4 Transform::matrix() const {
    return glm::translate(m_position) * glm::mat4_cast(m_orientation) * glm::scale(m_scale, m_scale, m_scale) * glm::translate(-m_center);
}

// should do the same as matrix() * vertex
glm::vec3 Transform::applyTo(const glm::vec3 &vertex) const {
    return m_position + (m_orientation * (m_scale * (-m_center + vertex)));
}

glm::vec3 Transform::inverseApplyTo(const glm::vec3 &vertex) const {
    return ((glm::inverse(m_orientation) * (vertex - m_position)) / m_scale) + m_center;
}

float Transform::scale() const {
    return m_scale;
}

void Transform::setScale(float scale) {
    assert(std::isfinite(scale) && scale > 0.0f);
    m_scale = scale;
}

const glm::vec3& Transform::center() const {
    return m_center;
}

void Transform::setCenter(const glm::vec3& center) {
    assert(std::isfinite(center));
    m_center = center;
}

bool Transform::operator==(const Transform &other) const {
    return m_position == other.m_position &&
           m_orientation == other.m_orientation &&
           m_center == other.m_center &&
           m_scale == other.m_scale;
}

bool Transform::operator!=(const Transform &other) const {
    return !(*this == other);
}

// calculate offset between old and new center and adjust position accordingly
void Transform::setCenterAndAdjustPosition(const glm::vec3& newCenter) {
    glm::vec3 oldOrigin = applyTo(glm::vec3(0.0f, 0.0f, 0.0f));
    setCenter(newCenter);
    glm::vec3 newOrigin = applyTo(glm::vec3(0.0f, 0.0f, 0.0f));

    setPosition(position() + (oldOrigin - newOrigin));
}


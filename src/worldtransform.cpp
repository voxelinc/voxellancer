#include "worldtransform.h"

#include <glow/logging.h>

WorldTransform::WorldTransform(glm::vec3 center, float scale) :
    m_position(0),
    m_orientation(),
    m_center(center),
    m_scale(scale)
{

}

WorldTransform::WorldTransform(const WorldTransform& worldTransform, const glm::vec3& positionDelta, const glm::quat& orientationDelta):
    WorldTransform(worldTransform)
{
    moveWorld(positionDelta);
    rotate(orientationDelta);
}

WorldTransform::~WorldTransform() {

}

const glm::quat& WorldTransform::orientation() const {
    return m_orientation;
}

void WorldTransform::setOrientation(const glm::quat& quat){
    assert(std::isfinite(quat.x));
    assert(std::isfinite(quat.y));
    assert(std::isfinite(quat.z));
    assert(std::isfinite(quat.w));
	m_orientation = quat;
}

const glm::vec3 &WorldTransform::position() const {
    return m_position;
}

void WorldTransform::setPosition(const glm::vec3& pos){
	m_position = pos;
}

// move in local axis direction
void WorldTransform::move(const glm::vec3& dist) {
    m_position += m_orientation * dist;
}

// move in world axis direction
void WorldTransform::moveWorld(const glm::vec3& dist) {
    m_position += dist;
}

// rotate around local axis
void WorldTransform::rotate(const glm::quat &qrot) {
    m_orientation = m_orientation * qrot;
}

void WorldTransform::rotateWorld(const glm::quat &qrot) {
    m_orientation = qrot * m_orientation;
}

const glm::mat4 WorldTransform::matrix() const {
    return glm::translate(m_position) * glm::mat4_cast(m_orientation) * glm::scale(m_scale, m_scale, m_scale) * glm::translate(-m_center);
}

// should do the same as matrix() * vertex
glm::vec3 WorldTransform::applyTo(const glm::vec3 &vertex) const {
    return m_position + (m_orientation * (m_scale * (-m_center + vertex)));
}

glm::vec3 WorldTransform::inverseApplyTo(const glm::vec3 &vertex) const {
    return ((glm::inverse(m_orientation) * (vertex - m_position)) / m_scale) + m_center;
}

float WorldTransform::scale() const {
    return m_scale;
}

void WorldTransform::setScale(float scale) {
    m_scale = scale;
}

const glm::vec3& WorldTransform::center() const {
    return m_center;
}

void WorldTransform::setCenter(const glm::vec3& center) {
    m_center = center;
}

bool WorldTransform::operator==(const WorldTransform &other) {
    return m_position == other.position() &&
           m_orientation == other.orientation() &&
           m_center == other.center() &&
           m_scale == other.scale();
}

bool WorldTransform::operator!=(const WorldTransform &other) {
    return !(*this == other);
}

// calculate offset between old and new center and adjust position accordingly
void WorldTransform::setCenterAndAdjustPosition(const glm::vec3& newCenter) {
    glm::vec3 oldOrigin = applyTo(glm::vec3(0));
    setCenter(newCenter);
    glm::vec3 newOrigin = applyTo(glm::vec3(0));

    setPosition(position() + (oldOrigin - newOrigin));
}


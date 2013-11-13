#include "worldtransform.h"

WorldTransform::WorldTransform() :
    m_position(0,0,0),
    m_orientation()
{

}

WorldTransform::WorldTransform(const glm::vec3 &position):
    m_position(position)
{
}

WorldTransform::WorldTransform(const glm::quat &orientation):
    m_orientation(orientation)
{
}

WorldTransform::~WorldTransform() {

}

void WorldTransform::clear() {
    m_position = glm::vec3(0,0,0);
    m_orientation = glm::quat();
}

const glm::quat WorldTransform::orientation() const {
    return m_orientation;
}

void WorldTransform::setOrientation(glm::quat quat){
	m_orientation = quat;
}

const glm::vec3 &WorldTransform::position() const {
    return m_position;
}

void WorldTransform::setPosition(glm::vec3 pos){
	m_position = pos;
}

void WorldTransform::move(glm::vec3 dist)
{
    m_position += dist * m_orientation;
}

void WorldTransform::rotateX(float rot)
{
    glm::quat qrot = glm::angleAxis(rot, glm::vec3(1, 0, 0));
    m_orientation = qrot * m_orientation;
}

void WorldTransform::rotateY(float rot)
{
    glm::quat qrot = glm::angleAxis(rot, glm::vec3(0, 1, 0));
    m_orientation = qrot * m_orientation;
}

void WorldTransform::rotateZ(float rot)
{
    glm::quat qrot = glm::angleAxis(rot, glm::vec3(0, 0, 1));
    m_orientation = qrot * m_orientation;
}

void WorldTransform::transform(const WorldTransform &other) {
    m_position += other.position();
    m_orientation = m_orientation * other.orientation();
}

const glm::mat4 WorldTransform::matrix() const {
    return glm::mat4_cast(m_orientation) * glm::translate(m_position);
}


void WorldTransform::applyTo(glm::vec3 &vertex) const {
    vertex = glm::vec3(matrix() * glm::vec4(vertex, 1.0f));
}


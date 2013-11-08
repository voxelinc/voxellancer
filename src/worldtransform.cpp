

#include "worldobject.h"

WorldTransform::WorldTransform() :
    m_position(0,0,0),
    m_orientation()
{

}

WorldTransform::~WorldTransform(){

}

void WorldTransform::move(glm::vec3 dist)
{
    m_position += dist * m_orientation;
}

void WorldTransform::moveTo(glm::vec3 pos){
	m_position = pos;
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

void WorldTransform::rotateTo(glm::quat quat){
	m_orientation = quat;
}

const glm::mat4 WorldTransform::matrix()
{
    return glm::mat4_cast(m_orientation) * glm::translate(m_position);
}

const glm::quat WorldTransform::orientation()
{
    return m_orientation;
}

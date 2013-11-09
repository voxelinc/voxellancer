

#include "worldobject.h"

WorldObject::WorldObject() :
    m_position(0,0,0),
    m_orientation()
{

}

WorldObject::~WorldObject(){

}

void WorldObject::move(glm::vec3 dist)
{
    m_position += dist * m_orientation;
}

void WorldObject::moveTo(glm::vec3 pos){
	m_position = pos;
}

void WorldObject::rotateX(float rot)
{
    glm::quat qrot = glm::angleAxis(rot, glm::vec3(1, 0, 0));
    m_orientation = qrot * m_orientation;
}

void WorldObject::rotateY(float rot)
{
    glm::quat qrot = glm::angleAxis(rot, glm::vec3(0, 1, 0));
    m_orientation = qrot * m_orientation;
}

void WorldObject::rotateZ(float rot)
{
    glm::quat qrot = glm::angleAxis(rot, glm::vec3(0, 0, 1));
    m_orientation = qrot * m_orientation;
}

void WorldObject::rotateTo(glm::quat quat){
	m_orientation = quat;
}

const glm::mat4 WorldObject::matrix()
{
    return glm::translate(m_position) * glm::mat4_cast(m_orientation);
}

const glm::quat WorldObject::orientation()
{
    return m_orientation;
}

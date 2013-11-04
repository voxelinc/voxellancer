
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include "player.h"

Player::Player():
    m_position(0,0,0),
    m_orientation()
{

}

void Player::move(glm::vec3 dist)
{
    m_position += dist * m_orientation;
}

void Player::rotateX(float rot)
{
    glm::quat qrot = glm::angleAxis(rot, glm::vec3(1, 0, 0));
    m_orientation = qrot * m_orientation;
}

void Player::rotateY(float rot)
{
    glm::quat qrot = glm::angleAxis(rot, glm::vec3(0, 1, 0));
    m_orientation = qrot * m_orientation;
}

void Player::rotateZ(float rot)
{
    glm::quat qrot = glm::angleAxis(rot, glm::vec3(0, 0, 1));
    m_orientation = qrot * m_orientation;
}

const glm::mat4 Player::matrix()
{
    return glm::mat4_cast(m_orientation) * glm::translate(m_position);
}

const glm::quat Player::orientation()
{
    return m_orientation;
}

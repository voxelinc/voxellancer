#include "follower.h"


Follower::Follower(float directionalAcceleration, float angularAcceleration):
    m_directionalAcceleration(directionalAcceleration),
    m_angularAcceleration(angularAcceleration)
{

}

const glm::vec3& Follower::position() const {
    return m_position;
}

const glm::vec3& Follower::orientation() const {
    return m_orientation;
}

void Follower::follow(const glm::vec3& targetPosition, glm::vec3& targetOrientation, float deltaSec) {

}


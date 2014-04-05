#include "inertiafollower.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "utils/tostring.h"


InertiaFollower::InertiaFollower(float directionalInertia, float angularInertia):
    m_directionalInertia(directionalInertia),
    m_angularInertia(angularInertia)
{

}

const glm::vec3& InertiaFollower::position() const {
    return m_position;
}

void InertiaFollower::setPosition(const glm::vec3& position) {
    m_position = position;
}

const glm::quat& InertiaFollower::orientation() const {
    return m_orientation;
}

void InertiaFollower::setOrientation(const glm::quat& orientation) {
    m_orientation = orientation;
}

void InertiaFollower::setInertia(float directional, float angular) {
    m_directionalInertia = directional;
    m_angularInertia = angular;
}

void InertiaFollower::follow(const glm::vec3& targetPosition, const glm::quat& targetOrientation, float deltaSec) {
    float mix = std::min(1.0f, m_directionalInertia * deltaSec);

    m_position = glm::mix(m_position, targetPosition, mix);
    m_orientation = glm::slerp(m_orientation, targetOrientation, mix);
}


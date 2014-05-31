#include "inertiafollower.h"

#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


InertiaFollower::InertiaFollower(float directionalInertia, float angularInertia):
    m_directionalInertia(directionalInertia),
    m_angularInertia(angularInertia)
{
    assert(directionalInertia >= 0 && directionalInertia <= 100 && angularInertia >= 0 && angularInertia <= 100);
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
    assert(directional >= 0 && directional <= 100 && angular >= 0 && angular <= 100);
    m_directionalInertia = directional;
    m_angularInertia = angular;
}

void InertiaFollower::follow(const glm::vec3& targetPosition, const glm::quat& targetOrientation, float deltaSec) {
    float positionMix = std::min(1.0f, (100.0f - m_directionalInertia) * deltaSec);
    float orientationMix = std::min(1.0f, (100.0f - m_angularInertia) * deltaSec);

    m_position = glm::mix(m_position, targetPosition, positionMix);
    m_orientation = glm::slerp(m_orientation, targetOrientation, orientationMix);
}


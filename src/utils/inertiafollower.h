#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

/**
 * Follows a position and orientation with a given inertia between
 * 0 = instant follow and 1 = never moves
 */
class InertiaFollower {
public:
    InertiaFollower(float directionalInertia, float angularInertia);

    const glm::vec3& position() const;
    void setPosition(const glm::vec3& position);

    const glm::quat& orientation() const;
    void setOrientation(const glm::quat& orientation);

    void setInertia(float directional, float angular);

    void follow(const glm::vec3& targetPosition, const glm::quat& targetOrientation, float deltaSec);


protected:
    glm::vec3 m_position;
    float m_directionalInertia;

    glm::quat m_orientation;
    float m_angularInertia;
};


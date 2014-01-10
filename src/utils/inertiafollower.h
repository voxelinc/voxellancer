#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>


// Listen to Mercenary - The Follower. Awesome song. We need more metal in this game.
class InertiaFollower {
public:
    InertiaFollower(float directionalInertia, float angularInertia);

    const glm::vec3& position() const;
    const glm::quat& orientation() const;

    void follow(const glm::vec3& targetPosition, const glm::quat& targetOrientation, float deltaSec);


protected:
    glm::vec3 m_position;
    float m_directionalInertia;

    glm::quat m_orientation;
    float m_angularInertia;
};

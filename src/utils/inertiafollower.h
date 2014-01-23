#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>


class InertiaFollower {
public:
    InertiaFollower(float directionalInertia, float angularInertia);

    const glm::vec3& position() const;
    void setPosition(const glm::vec3& position);

    const glm::quat& orientation() const;
    void setOrientation(const glm::quat& orientation);

    void follow(const glm::vec3& targetPosition, const glm::quat& targetOrientation, float deltaSec);


protected:
    glm::vec3 m_position;
    float m_directionalInertia;

    glm::quat m_orientation;
    float m_angularInertia;
};

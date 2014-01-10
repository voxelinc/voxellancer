#pragma once

#include <glm/glm.hpp>


// Listen to Mercenary - The Follower. Awesome song. We need more metal in this game.
class Follower {
public:
    Follower(float directionalAcceleration, float angularAcceleration);

    const glm::vec3& position() const;
    const glm::vec3& orientation() const;

    void follow(const glm::vec3& targetPosition, const glm::vec3& targetOrientation, float deltaSec);


protected:
    glm::vec3 m_position;
    glm::vec3 m_directionalSpeed;
    float m_directionalAcceleration;

    glm::vec3 m_orientation;
    glm::vec3 m_angularSpeed;
    float m_angularAcceleration;
};

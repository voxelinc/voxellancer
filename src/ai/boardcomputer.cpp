#include "boardcomputer.h"

#include <glm/gtc/quaternion.hpp>

#include "worldobject/ship.h"

BoardComputer::BoardComputer(Ship& ship) :
    m_ship(ship)
{
}

// accelerates towards position. Tries to keep a minimum distance of minDistance to the target
void BoardComputer::moveTo(glm::vec3 position, float minDistance) {
    glm::vec3 delta = position - m_ship.transform().position();
    glm::vec3 direction = glm::normalize(delta);
    float distance = glm::length(delta);

    if (distance < minDistance) {
        m_ship.accelerate(-direction);
    } else if (distance < minDistance*2) {
        float f = (distance - minDistance) / minDistance;
        m_ship.accelerate(direction*f);
    }
    else {
        m_ship.accelerate(direction);
    }

}

float angleBetween(glm::vec3 u, glm::vec3 v) {
    float angle = glm::acos(glm::dot(glm::normalize(u), glm::normalize(v)));
    assert(isfinite(angle));
    return angle;
}

glm::quat quatFrom(glm::vec3 u, glm::vec3 v) {
    float angle = angleBetween(u, v);
    glm::vec3 w = glm::normalize(glm::cross(u, v));
    return glm::angleAxis(angle, w);
}

void BoardComputer::rotateTo(glm::vec3 position) {
    float minDelta = glm::pi<float>() / 24.0f; // 5 degrees
    glm::vec3 shipDirection = m_ship.transform().orientation() * glm::vec3(0, 0, -1);
    glm::vec3 targetDirection = position - m_ship.transform().position();
    glm::quat rotation = quatFrom(shipDirection, targetDirection);

    if (glm::abs(glm::angle(rotation)) > minDelta) {
        glm::vec3 euler = glm::eulerAngles(rotation);
        m_ship.accelerateAngular(glm::normalize(euler));
    }
}

void BoardComputer::shootBullet(const std::list<std::shared_ptr<WorldObjectHandle>>& targets) {
    float max_angle = glm::pi<float>() / 6.0f;  // 30 degree
    
    for (auto targetHandle : targets) {
        if (WorldObject* target = targetHandle->get()) {
            glm::vec3 shipDirection = m_ship.transform().orientation() * glm::vec3(0, 0, -1);
            glm::vec3 targetDirection = target->transform().position() - m_ship.transform().position();
            float angle = angleBetween(shipDirection, targetDirection);
            if (glm::abs(angle) < max_angle) {
                m_ship.fireAtPoint(target->transform().position());
            }
        }
    }
}

void BoardComputer::shootRockets(std::shared_ptr<WorldObjectHandle> target) {
    if (target->get()) {
        m_ship.setTargetObject(target->get());
        m_ship.fireAtObject();
    }
}

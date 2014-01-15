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
    glm::vec3 direction = glm::inverse(m_ship.transform().orientation()) * glm::normalize(delta);
    float distance = glm::length(delta);

    if (distance < minDistance) {
        m_ship.accelerate(-direction);
    } else if (distance < minDistance*2) {
        float f = (distance - minDistance*1.5f) / minDistance;
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
    glm::vec3 shipDirection =  glm::vec3(0, 0, -1);
    glm::vec3 targetDirection = glm::inverse(m_ship.transform().orientation()) * glm::normalize(position - m_ship.transform().position());
    glm::quat rotation = quatFrom(shipDirection, targetDirection);

    if (glm::abs(glm::angle(rotation)) > minDelta) {
        glm::vec3 euler = glm::eulerAngles(rotation);
        m_ship.accelerateAngular(glm::normalize(euler)*0.1f);
    }
}
//
//glm::vec3 targetDirection = glm::inverse(m_ship.transform().orientation()) * glm::normalize(position - m_ship.transform().position());
//glm::vec3 shipDirection = glm::vec3(0, 0, -1);
//glm::vec3 w = glm::cross(targetDirection, shipDirection);
//glm::quat rotation;
//if (w != glm::vec3(0)) {
//    glm::vec3 rotationAxis = glm::normalize(w);
//    float angle = glm::acos(glm::dot(targetDirection, shipDirection));
//    if (angle > glm::radians(0.1)) {
//        rotation = glm::angleAxis(-angle, rotationAxis);
//    }
//} else { // the target is either perfectly in front or behind us
//    if (targetDirection == -shipDirection) {
//        rotation = glm::angleAxis(glm::pi<float>() / 2, glm::vec3(1, 0, 0));
//    }
//}
//
//float minAngle = glm::pi<float>() / 24.0f; // 5 degree
//float f = 1;
//if (distance < minAngle) {
//    f = -1;
//} else if (distance < minDistance * 2) {
//    float f = (distance - minDistance*1.5f) / minDistance * glm::min(glm::length(m_ship.physics().speed() * 0.2f), 1.0f);
//}
//
//if (rotation != glm::quat()) {
//    m_ship.accelerateAngular((0.2f * glm::normalize(glm::eulerAngles(rotation))));
//}


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

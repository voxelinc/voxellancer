#include "boardcomputer.h"

#include <cmath>

#include <glm/gtc/quaternion.hpp>

#include "worldobject/ship.h"
#include "utils/randvec.h"


BoardComputer::BoardComputer(Ship& ship) :
    m_ship(ship)
{
}

// accelerates towards position. Tries to keep a minimum distance of minDistance to the target
void BoardComputer::moveTo(const glm::vec3& position) {
    glm::vec3 projectedPosition = m_ship.physics().projectedTransformIn(1.0f).position();

    glm::vec3 delta = position - projectedPosition;
    glm::vec3 direction = glm::inverse(m_ship.transform().orientation()) * glm::normalize(delta);
    float distance = glm::length(delta);

    
        m_ship.accelerate(direction);
    
    

}

float angleBetween(const glm::vec3& u, const glm::vec3& v) {
    float angle = glm::acos(glm::clamp(glm::dot(glm::normalize(u), glm::normalize(v)), 0.0f, 1.0f));
    assert(std::isfinite(angle));
    return angle;
}

glm::quat quatFrom(const glm::vec3& u, const glm::vec3& v) {
    float angle = angleBetween(u, v);
    glm::vec3 w = glm::cross(u, v);
    if (w == glm::vec3(0)) {
        w = RandVec3::randUnitVec();
    }
    return glm::angleAxis(angle, glm::normalize(w));
}

void BoardComputer::rotateTo(const glm::vec3& position, const glm::vec3& up) {
    float minDelta = glm::radians(5.0f);
    glm::quat projectedOrientation = glm::inverse(m_ship.transform().orientation()) * m_ship.physics().projectedTransformIn(1.0f).orientation();

    glm::vec3 shipDirection = projectedOrientation * glm::vec3(0, 0, -1);
    glm::vec3 targetDirection = glm::inverse(m_ship.transform().orientation()) * glm::normalize(position - m_ship.transform().position());
    glm::quat rotation = quatFrom(shipDirection, targetDirection);

    if (up != glm::vec3(0, 0, 0)){
        glm::vec3 upDirection = glm::vec3(0, 1, 0);
        glm::vec3 newUpDirection = glm::inverse(m_ship.transform().orientation()) * glm::normalize(up);
        glm::quat upRotation = quatFrom(upDirection, newUpDirection);
        rotation = upRotation * rotation; // glm::slerp(glm::quat(), upRotation, 0.2f);
    } else {
        //TODO: make it look naturally, e.g. up is to the "inside" of the rotation
        if(glm::abs(glm::angle(rotation)) > glm::radians(20.0f)) {
            glm::vec3 upDirection = glm::vec3(0, 1, 0);
            glm::vec3 newUpDirection = glm::vec3(0, 0, 1) + (rotation * glm::vec3(0, 0, -1)); //glm::slerp(glm::quat(), rotation, 0.5f) * glm::vec3(0, 0, -1);
            glm::quat upRotation = quatFrom(upDirection, newUpDirection);
            rotation = upRotation * rotation; // glm::slerp(glm::quat(), upRotation, 0.2f);
        }
    }

    if (glm::abs(glm::angle(rotation)) > minDelta) {
        glm::vec3 euler = glm::eulerAngles(rotation);
        m_ship.accelerateAngular(glm::normalize(euler) * 0.2f);
    }
}

void BoardComputer::shootBullet(const std::list<std::shared_ptr<WorldObjectHandle>>& targets) {
    float max_angle = glm::radians(45.0f);

    for (auto targetHandle : targets) {
        if (WorldObject* target = targetHandle->get()) {
            glm::vec3 shipDirection = m_ship.transform().orientation() * glm::vec3(0, 0, -1);
            glm::vec3 targetDirection = target->transform().position() - m_ship.transform().position();
            float angle = angleBetween(shipDirection, targetDirection);
            if (glm::abs(angle) < max_angle) {
                glm::vec3 offset = RandVec3::rand(0, 1) * glm::length(targetDirection) / 30.0f;
                m_ship.fireAtPoint(target->transform().position() + offset);
                break;
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

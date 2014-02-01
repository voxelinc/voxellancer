#include "boardcomputer.h"

#include <cmath>

#include <glm/gtc/quaternion.hpp>

#include "worldobject/ship.h"
#include "utils/randvec.h"
#include "utils/geometryhelper.h"


static const float s_minActDistance = 0.1f;
static const float s_minActAngle = glm::radians(1.0f);
static const float s_minAutoUpAngle = glm::radians(10.0f);

BoardComputer::BoardComputer(Ship& ship) :
    m_ship(ship)
{
}

void BoardComputer::moveTo(const glm::vec3& position) {
    glm::vec3 projectedPosition = m_ship.physics().projectedTransformIn(1.0f).position();

    glm::vec3 delta = position - projectedPosition;
    glm::vec3 direction = glm::inverse(m_ship.transform().orientation()) * glm::normalize(delta);
    float distance = glm::length(delta);

    if (distance > s_minActDistance) {
        Acceleration acceleration(direction, m_ship.components().currentRelativeAcceleration().angular());
        m_ship.components().setCurrentRelativeAcceleration(acceleration);
    }
}

void BoardComputer::rotateTo(const glm::vec3& position, const glm::vec3& up) {
    glm::quat projectedOrientation = glm::inverse(m_ship.transform().orientation()) * m_ship.physics().projectedTransformIn(1.0f).orientation();

    glm::vec3 shipDirection = projectedOrientation * glm::vec3(0, 0, -1);
    glm::vec3 targetDirection = glm::inverse(m_ship.transform().orientation()) * glm::normalize(position - m_ship.transform().position());
    glm::quat rotation = GeometryHelper::quatFromTo(shipDirection, targetDirection);

    if (glm::abs(glm::angle(rotation)) > s_minActAngle) {
        glm::vec3 euler = glm::eulerAngles(rotation);

        Acceleration acceleration(m_ship.components().currentRelativeAcceleration().directional(), glm::normalize(euler));
        m_ship.components().setCurrentRelativeAcceleration(acceleration);
    }

    if (up != glm::vec3(0, 0, 0)){
        rotateUpTo(up);
    } else {
        rotateUpAuto(rotation);
    }

}

void BoardComputer::rotateUpTo(const glm::vec3& up) {
    glm::vec3 upDirection = glm::vec3(0, 1, 0);
    glm::vec3 newUpDirection = glm::inverse(m_ship.transform().orientation()) * glm::normalize(up);
    glm::quat upRotation = GeometryHelper::quatFromTo(upDirection, newUpDirection);
    glm::vec3 euler = glm::eulerAngles(upRotation);

    Acceleration acceleration(m_ship.components().currentRelativeAcceleration().directional(), glm::normalize(euler));
    m_ship.components().setCurrentRelativeAcceleration(acceleration);
}

void BoardComputer::rotateUpAuto(const glm::quat& rotation) {
    //make it look naturally, e.g. up is to the "inside" of the rotation
    if (glm::abs(glm::angle(rotation)) > s_minAutoUpAngle) {
        glm::vec3 upDirection = glm::vec3(0, 1, 0);
        glm::vec3 newUpDirection = glm::vec3(0, 0, 1) + (rotation * glm::vec3(0, 0, -1));
        glm::quat upRotation = GeometryHelper::quatFromTo(upDirection, newUpDirection);
        glm::vec3 euler = glm::eulerAngles(upRotation);

        Acceleration acceleration(m_ship.components().currentRelativeAcceleration().directional(), glm::normalize(euler));
        m_ship.components().setCurrentRelativeAcceleration(acceleration);
    }
}

void BoardComputer::shootBullet(const std::list<Handle<WorldObject>>& targets) {
    float max_angle = glm::radians(45.0f);

    for (auto targetHandle : targets) {
        if (WorldObject* target = targetHandle.get()) {
            glm::vec3 shipDirection = m_ship.transform().orientation() * glm::vec3(0, 0, -1);
            glm::vec3 targetDirection = target->transform().position() - m_ship.transform().position();
            float angle = GeometryHelper::angleBetween(shipDirection, targetDirection);
            if (glm::abs(angle) < max_angle) {
                glm::vec3 offset = RandVec3::rand(0, 1) * glm::length(targetDirection) / 30.0f;
                m_ship.components().fireAtPoint(target->transform().position() + offset);
                break;
            }
        }
    }
}

void BoardComputer::shootRockets(Handle<WorldObject> target) {
    if (target.valid()) {
        m_ship.setTargetObject(target.get());
        m_ship.components().fireAtObject(target.get());
    }
}

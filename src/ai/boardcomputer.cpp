#include "boardcomputer.h"

#include <cmath>

#include <glm/gtc/quaternion.hpp>

#include "collision/collisionfilter.h"

#include "utils/safenormalize.h"
#include "utils/randvec3.h"
#include "utils/geometryhelper.h"

#include "physics/physics.h"

#include "worldobject/ship.h"
#include "worldobject/worldobjectcomponents.h"

#include "equipment/hardpoint.h"
#include "equipment/weapon.h"
#include "equipment/weapons/gun.h"


static const float s_minActDistance = 0.5f;
static const float s_minActAngle = glm::radians(2.0f);
static const float s_minAutoUpAngle = glm::radians(10.0f);

BoardComputer::BoardComputer(WorldObject* worldObject) :
    m_worldObject(worldObject),
    m_overwriteEngineState(false)
{
}

WorldObject* BoardComputer::worldObject() {
    return m_worldObject;
}

const EngineState& BoardComputer::engineState() const {
    return m_engineState;
}

void BoardComputer::moveTo(const glm::vec3& position, bool decelerate) {
    glm::vec3 projectedPosition = m_worldObject->physics().speed().moved(m_worldObject->transform(), 1.0f).position();
    glm::vec3 delta = position - projectedPosition;
    float distance = glm::length(delta);

    if (distance > s_minActDistance) {
        if (!decelerate && m_worldObject->physics().speed().directional() != glm::vec3(0)) {
            glm::vec3 currentPosition = m_worldObject->transform().position();
            float angleFromProjected = GeometryHelper::angleBetween(m_worldObject->physics().speed().directional(), delta);
            float angleFromCurrent = GeometryHelper::angleBetween(m_worldObject->physics().speed().directional(), position - currentPosition);

            if (angleFromCurrent < glm::quarter_pi<float>() && angleFromProjected > glm::half_pi<float>()) {
                // the projection is already past the target, but we don't want to deaccelerate
                // instead, project the target from our current position to a sphere around our position
                float projectionDistance = glm::length(projectedPosition - currentPosition);
                glm::vec3 fakePosition = currentPosition + safeNormalize(position - currentPosition, glm::vec3(0, 0, 0)) * 1.5f * projectionDistance;

                delta = fakePosition - projectedPosition;
            }
        }

        glm::vec3 direction = glm::inverse(m_worldObject->transform().orientation()) * safeNormalize(delta, glm::vec3(0, 0, 0));
        m_engineState.setDirectional(direction);
    }

    m_overwriteEngineState = true;
}

void BoardComputer::rotateTo(const glm::vec3& position, const glm::vec3& up) {
    glm::vec3 accumulatedEuler;

    // A guess (hack) where the WorldObject will point to in one second, in the local coordinate-sys
    glm::quat projectedOrientation = glm::inverse(m_worldObject->transform().orientation()) * m_worldObject->physics().speed().moved(m_worldObject->transform(), 0.1f).orientation();
    glm::vec3 projectedDirection = projectedOrientation * glm::vec3(0, 0, -1);

    // Direction to the target, in the local coordinate-sys
    if (position == m_worldObject->transform().position()) {
        return;
    }

    auto deltaToTarget = safeNormalize(position - m_worldObject->transform().position());
    glm::vec3 targetDirection = deltaToTarget.valid() ?
                                    glm::inverse(m_worldObject->transform().orientation()) * deltaToTarget.get() :
                                    glm::vec3(0, 0, 1);

    // The rotation that needs to be performed, in the local coordinate-sys
    glm::quat rotation = GeometryHelper::quatFromTo(projectedDirection, targetDirection);

    if (glm::abs(glm::angle(rotation)) > s_minActAngle) {
        accumulatedEuler = glm::eulerAngles(rotation);

    }

    if (up != glm::vec3(0, 0, 0)){
        accumulatedEuler += rotateUpTo(up);
    } else {
        accumulatedEuler += rotateUpAuto(rotation);
    }

    accumulatedEuler = glm::sign(accumulatedEuler);
    m_engineState.setAngular(accumulatedEuler);

    m_overwriteEngineState = true;
}

glm::vec3 BoardComputer::rotateUpTo(const glm::vec3& up) {
    glm::vec3 upDirection = glm::vec3(0, 1, 0);
    glm::vec3 newUpDirection = glm::inverse(m_worldObject->transform().orientation()) * safeNormalize(up, glm::vec3(0, 1, 0));
    glm::quat upRotation = GeometryHelper::quatFromTo(upDirection, newUpDirection);

    if (glm::abs(glm::angle(upRotation)) > s_minActAngle) {
        glm::vec3 euler = glm::eulerAngles(upRotation);
        return euler * 0.5f;
    }

    return glm::vec3(0.0f);
}

glm::vec3 BoardComputer::rotateUpAuto(const glm::quat& rotation) {
    //make it look naturally, e.g. up is to the "inside" of the rotation
    if (glm::abs(glm::angle(rotation)) > s_minAutoUpAngle) {
        glm::vec3 upDirection = glm::vec3(0, 1, 0);
        glm::vec3 newUpDirection = glm::vec3(0, 0, 1) + (rotation * glm::vec3(0, 0, -1));
        glm::quat upRotation = GeometryHelper::quatFromTo(upDirection, newUpDirection);
        glm::vec3 euler = glm::eulerAngles(upRotation);

        return euler * 0.5f;
    }

    return glm::vec3(0.0f);
}

void BoardComputer::shootBullet(const std::vector<Handle<WorldObject>>& targets) {
    float max_angle = glm::radians(45.0f);

    for (auto& targetHandle : targets) {
        if (const WorldObject* target = targetHandle.get()) {
            // Hardpoints check themselves whether they can fire, just tell everyone to shoot everything
            glm::vec3 targetDirection = target->position() - m_worldObject->position();
            glm::vec3 inaccuracyNoise = RandVec3::rand(0, 1) * glm::length(targetDirection) / 30.0f;

            glm::vec3 targetPoint = target->position() + inaccuracyNoise;

            m_worldObject->components().fireAtPoint(targetPoint, true);
        }
    }
}

void BoardComputer::shootRockets(WorldObject* target) {
    m_worldObject->components().fireAtObject(target);
}

void BoardComputer::update(float deltaSec) {
    if(m_overwriteEngineState) {
        m_worldObject->components().setEngineState(m_engineState);
    }
    m_engineState.clear();
    m_overwriteEngineState = false;
}



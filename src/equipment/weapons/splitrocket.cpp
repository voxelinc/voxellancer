#include "splitrocket.h"

#include <glow/logging.h>

#include "ai/basictasks/splitrockettask.h"

#include "equipment/weapons/bullet.h"

#include "physics/physics.h"

#include "resource/worldobjectbuilder.h"

#include "utils/geometryhelper.h"
#include "utils/randfloatpool.h"

#include "voxel/voxelclusterbounds.h"

#include "voxeleffect/voxelexplosiongenerator.h"

#include "worldobject/worldobject.h"


SplitRocket::SplitRocket():
    m_childrenSpeedBoost(0.0f),
    m_childrenSpeedBoostRandomization(0.0f),
    m_splitDistance(150.0f),
    m_splitDirectionTolerance(30.0f),
    m_splitAngle(glm::quarter_pi<float>()),
    m_splitAngleRandomization(0.0f),
    m_minFlytimeBeforeSplit(0.0f)
{

}

void SplitRocket::setTarget(WorldObject* targetObject) {
    if (targetObject) {
        m_targetHandle = makeHandle(targetObject);
        m_aiTask.reset(new SplitRocketTask(this, &m_boardComputer, targetObject));
    } else {
        m_targetHandle = Handle<WorldObject>(nullptr);
        m_aiTask.reset(nullptr);
    }
}

void SplitRocket::setChildrenCount(int count) {
    m_childrenCount = count;
}

void SplitRocket::setChildrenType(const std::string& type) {
    m_childrenType = type;
}

float SplitRocket::childrenSpeedBoost() const {
    return m_childrenSpeedBoost;
}

void SplitRocket::setChildrenSpeedBoost(float childrenSpeedBoost) {
    m_childrenSpeedBoost = childrenSpeedBoost;
}

float SplitRocket::childrenSpeedBoostRandomization() const {
    return m_childrenSpeedBoostRandomization;
}

void SplitRocket::setChildrenSpeedBoostRandomization(float childrenSpeedBoostRandomization) {
    m_childrenSpeedBoostRandomization = childrenSpeedBoostRandomization;
}

float SplitRocket::splitDistance() const {
    return m_splitDistance;
}

void SplitRocket::setSplitDistance(float splitDistance) {
    m_splitDistance = splitDistance;
}

float SplitRocket::splitDirectionTolerance() const {
    return m_splitDirectionTolerance;
}

void SplitRocket::setSplitDirectionTolerance(float splitDirectionTolerance) {
    m_splitDirectionTolerance = splitDirectionTolerance;
}

float SplitRocket::splitAngle() const {
    return m_splitAngle;
}

void SplitRocket::setSplitAngle(float splitAngle) {
    m_splitAngle = splitAngle;
}

float SplitRocket::splitAngleRandomization() const {
    return m_splitAngleRandomization;
}

void SplitRocket::setSplitAngleRandomization(float splitAngleRandomization) {
    m_splitAngleRandomization = splitAngleRandomization;
}

float SplitRocket::minFlytimeBeforeSplit() const {
    return m_minFlytimeBeforeSplit;
}

void SplitRocket::setMinFlytimeBeforeSplit(float minFlytimeBeforeSplit) {
    m_minFlytimeBeforeSplit = minFlytimeBeforeSplit;
}

void SplitRocket::split() {
    spawnChildren();
    spawnExplosion();

    scheduleRemoval();
}

void SplitRocket::spawnChildren() {
    if (m_targetHandle.valid()) {
        for (int i = 0; i < m_childrenCount; i++) {
            WorldObject* child = WorldObjectBuilder(m_childrenType).build();

            float splitAngle = RandFloatPool::randomize(m_splitAngle, m_splitAngleRandomization);

            glm::quat circleOrientation = glm::angleAxis(2 * glm::pi<float>() * i / m_childrenCount, glm::vec3(0, 0, -1));
            glm::quat splitOrientation = glm::angleAxis(splitAngle, glm::vec3(1, 0, 0));

            glm::quat launchOrientation = transform().orientation() * circleOrientation * splitOrientation;
            glm::vec3 spawnOffset = transform().orientation() * circleOrientation * glm::vec3(0, 1, 0);
            glm::vec3 rocketPosition = position() + circleOrientation * spawnOffset;

            child->transform().setOrientation(launchOrientation);
            child->transform().setPosition(rocketPosition);

            setChildSpeed(child, launchOrientation);

            if (child->objectType() == WorldObjectType::Rocket) {
                static_cast<Rocket*>(child)->setCreator(m_creator);
                static_cast<Rocket*>(child)->setTarget(m_targetHandle.get());
            }

            if (child->objectType() == WorldObjectType::Bullet) {
                static_cast<Bullet*>(child)->setCreator(m_creator);
            }

            child->setUniverse(universe());
            child->setSector(sector());

            child->spawn();
        }
    }
}

void SplitRocket::setChildSpeed(WorldObject* child, const glm::quat& launchOrientation) {
    Speed speed(physics().speed());

    speed.setDirectional(launchOrientation * glm::vec3(0, 0, -1) * glm::length(speed.directional()));

    if (glm::length(speed.directional()) > 0.0f) {
        glm::vec3 boostDirection = glm::normalize(speed.directional());
        glm::vec3 boost = boostDirection * RandFloatPool::randomize(m_childrenSpeedBoost, m_childrenSpeedBoostRandomization);
        speed.setDirectional(speed.directional() + boost);
    }

    child->physics().setSpeed(speed);
}

void SplitRocket::spawnExplosion() {
    VoxelExplosionGenerator generator(this);

    generator.setPosition(m_transform.position());
    generator.setScale(m_transform.scale() / 3.0f);
    generator.setColor(0xFFAA00);
    generator.setEmissiveness(0.4f);
    generator.setCount(300);
    generator.setLifetime(1.5f, 0.2f);
    generator.setForce(0.5f);

    generator.spawn();
}


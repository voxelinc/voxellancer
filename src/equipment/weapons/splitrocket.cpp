#include "splitrocket.h"

#include "ai/basictasks/splitrockettask.h"

#include "physics/physics.h"

#include "resource/worldobjectbuilder.h"

#include "utils/geometryhelper.h"

#include "voxeleffect/voxelexplosiongenerator.h"

#include "voxel/voxelclusterbounds.h"

#include "world/god.h"
#include "world/world.h"


SplitRocket::SplitRocket():
    m_splitDistance(150.0f),
    m_splitDirectionTolerance(30.0f),
    m_splitAngle(glm::quarter_pi<float>()),
    m_minFlytimeBeforeSplit(0.0f)
{

}

void SplitRocket::setTarget(WorldObject* targetObject) {
    if (targetObject) {
        m_targetHandle = targetObject->handle();
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

float SplitRocket::minFlytimeBeforeSplit() const {
    return m_minFlytimeBeforeSplit;
}

void SplitRocket::setMinFlytimeBeforeSplit(float minFlytimeBeforeSplit) {
    m_minFlytimeBeforeSplit = minFlytimeBeforeSplit;
}

void SplitRocket::split() {
    spawnChildren();
    spawnExplosion();

    World::instance()->god().scheduleRemoval(this);
}

void SplitRocket::spawnChildren() {
    if (m_targetHandle.valid()) {
        for (int i = 0; i < m_childrenCount; i++) {
            Rocket* rocket = WorldObjectBuilder(m_childrenType).buildRocket();

            glm::quat circleOrientation = glm::angleAxis(2 * glm::pi<float>() * i / m_childrenCount, glm::vec3(0, 0, -1));
            glm::quat splitOrientation = glm::angleAxis(m_splitAngle, glm::vec3(1, 0, 0));

            glm::quat launchOrientation = transform().orientation() * circleOrientation * splitOrientation;
            glm::vec3 spawnOffset = transform().orientation() * circleOrientation * glm::vec3(0, 1, 0);
            glm::vec3 rocketPosition = position() + circleOrientation * spawnOffset;

            rocket->transform().setOrientation(launchOrientation);
            rocket->transform().setPosition(rocketPosition);

            rocket->setCreator(m_creator);
            rocket->setTarget(m_targetHandle.get());

            rocket->physics().setSpeed(physics().speed());

            World::instance()->god().scheduleSpawn(rocket);
        }
    }
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

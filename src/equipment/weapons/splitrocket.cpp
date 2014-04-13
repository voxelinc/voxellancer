#include "splitrocket.h"

#include "ai/basictasks/splitrockettask.h"

#include "physics/physics.h"

#include "resource/worldobjectbuilder.h"

#include "utils/geometryhelper.h"

#include "voxeleffect/voxelexplosiongenerator.h"

#include "voxel/voxelclusterbounds.h"

#include "world/god.h"
#include "world/world.h"

static float s_detonationDistance = 100.0f;
static float s_detonationFieldOfAim = glm::radians(30.0f);
static float s_childrenCount = 5;
static std::string s_childrenRocketName = "hornet";


void SplitRocket::setTarget(WorldObject* targetObject) {
    if (targetObject) {
        m_targetHandle = targetObject->handle();
        m_aiTask.reset(new SplitRocketTask(this, &m_boardComputer, targetObject));
    } else {
        m_targetHandle = Handle<WorldObject>(nullptr);
        m_aiTask.reset(nullptr);
    }
}

float SplitRocket::detonationDistance() {
    return s_detonationDistance;
}

float SplitRocket::detonationFieldOfAim() {
    return s_detonationFieldOfAim;
}

void SplitRocket::detonate() {
    World::instance()->god().scheduleRemoval(this);
    spawnChildren();
    spawnExplosion();
}

void SplitRocket::spawnChildren() {
    if (m_targetHandle.valid()) {
        for (int i = 0; i < s_childrenCount; i++) {
            Rocket* rocket = WorldObjectBuilder(s_childrenRocketName).buildRocket();
            glm::quat circleOrientation = glm::angleAxis(2 * glm::pi<float>() * i / s_childrenCount, glm::vec3(0, 0, -1));
            glm::quat splitOrientation = glm::angleAxis(glm::quarter_pi<float>(), glm::vec3(1, 0, 0));

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
    generator.setColor(0xFF0000);
    generator.setEmissiveness(0.4f);
    generator.setCount(300);
    generator.setLifetime(1.5f, 0.2f);
    generator.setForce(0.5f);

    generator.spawn();
}
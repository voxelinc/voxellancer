#include "enginetrailgenerator.h"

#include "utils/tostring.h"
#include "utils/geometryhelper.h"

#include "voxel/specialvoxels/engineslotvoxel.h"

#include "worldobject/components/engine.h"
#include "worldobject/components/engineslot.h"
#include "worldobject/worldobject.h"
#include "voxelexplosiongenerator.h"
#include "physics/physics.h"
#include "worldobject/worldobjectcomponents.h"


EngineTrailGenerator::EngineTrailGenerator(Engine* engine) :
    m_generator(new VoxelExplosionGenerator()),
    m_engine(engine),
    m_spawnOffset(0.5f),
    m_lastValid(false),
    m_stepRest(0.0f),
    m_timeSinceLastSpawn(0),
    prop_stepDistance("vfx.engineTrailStepDistance"),
    prop_idleTime("vfx.engineTrailIdleCooldown")
{
    assert(engine != nullptr);

    m_generator->setColor(0x6666FF);
    m_generator->setEmissiveness(0.4f);
    m_generator->setCount(8);
    m_generator->setForce(0.10f, 0.3f);
    m_generator->setLifetime(1.0f, 0.1f);
}

EngineTrailGenerator::~EngineTrailGenerator() = default;

void EngineTrailGenerator::setLifetime(float lifetime) {
    m_generator->setLifetime(lifetime, 0.1f);
}

void EngineTrailGenerator::update(float deltaSec) {
    assert(m_engine);

    if(m_engine->engineSlot()) { // Only spawn if engine is installed
        m_timeSinceLastSpawn += deltaSec;

        updateTrailSettings();

        if (m_engine->state().directional().z <= -0.05f) { //only when moving forward
            spawnTrail();
        } else {
            if (m_timeSinceLastSpawn > prop_idleTime) { // When not moving, we still want some exhausts
                spawnAt(calculateSpawnPosition());
            }
        }

        m_lastSpawnPoint = calculateSpawnPosition();
    }
}

void EngineTrailGenerator::spawnTrail() {
    WorldObject* worldObject = m_engine->engineSlot()->components()->worldObject();

    m_spawnOffset = worldObject->transform().scale() * 1.2f;

    glm::vec3 newPosition = calculateSpawnPosition();
    glm::vec3 distance = newPosition - m_lastSpawnPoint;
    glm::vec3 step = GeometryHelper::safeNormalize(distance) * prop_stepDistance.get();
    glm::vec3 currentPosition = m_lastSpawnPoint;

    float stepCount = glm::length(distance) / prop_stepDistance;

    m_stepRest += std::fmod(stepCount, 1.0f);

    stepCount += static_cast<int>(m_stepRest);
    m_stepRest -= glm::floor(m_stepRest);

    for (int i = 0; i < stepCount; i++){
        currentPosition += step;
        spawnAt(currentPosition);
    }
}

glm::vec3 EngineTrailGenerator::calculateSpawnPosition() {
    WorldObject* worldObject = m_engine->engineSlot()->components()->worldObject();
    return m_engine->engineSlot()->position() + worldObject->transform().orientation() * glm::vec3(0, 0, m_spawnOffset);
}

void EngineTrailGenerator::spawnAt(glm::vec3 position) {
    WorldObject* worldObject = m_engine->engineSlot()->components()->worldObject();

    m_generator->setPosition(position);
    m_generator->setImpactVector(worldObject->transform().orientation() * (glm::vec3(0, 0, 0.1f) * glm::abs(worldObject->physics().acceleration().directional()) / 5.0f));

    m_generator->spawn();
    m_timeSinceLastSpawn = 0.0f;
    m_lastSpawnPoint = position;
}

/*
    The worldobject and therefor the radius and scale of the particles
    may change every frame, so the only way to really ensure safety here is to set
    them very frame
*/
void EngineTrailGenerator::updateTrailSettings() {
    WorldObject* worldObject = m_engine->engineSlot()->components()->worldObject();

    m_generator->setScale(worldObject->transform().scale() / 15.0f);
    m_generator->setRadius(worldObject->transform().scale() * 0.3f);
}


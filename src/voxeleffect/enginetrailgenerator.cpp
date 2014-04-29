#include "enginetrailgenerator.h"

#include "utils/tostring.h"
#include "utils/glmext/safenormalize.h"
#include "utils/geometryhelper.h"

#include "voxel/specialvoxels/engineslotvoxel.h"

#include "equipment/engine.h"
#include "equipment/engineslot.h"
#include "worldobject/worldobject.h"
#include "voxelexplosiongenerator.h"
#include "physics/physics.h"
#include "worldobject/worldobjectcomponents.h"


EngineTrailGenerator::EngineTrailGenerator(Engine& engine, const WorldObject& creator) :
    m_generator(new VoxelExplosionGenerator(nullptr)),
    m_creator(creator),
    m_engine(engine),
    m_spawnOffset(0.5f),
    m_lastValid(false),
    m_stepRest(0.0f),
    m_timeSinceLastSpawn(0),
    prop_stepDistance("vfx.engineTrailStepDistance"),
    prop_idleTime("vfx.engineTrailIdleCooldown")
{
    m_generator->setColor(0x6666FF);
    m_generator->setEmissiveness(0.4f);
    m_generator->setCount(4);
    m_generator->setForce(0.10f, 0.3f);
    m_generator->setLifetime(1.0f, 0.1f);
}

EngineTrailGenerator::~EngineTrailGenerator() = default;

void EngineTrailGenerator::setLifetime(float lifetime) {
    m_generator->setLifetime(lifetime, 0.1f);
}

void EngineTrailGenerator::setColor(int color) {
    m_generator->setColor(color);
}

void EngineTrailGenerator::setEmissiveness(float emissiveness) {
    m_generator->setEmissiveness(emissiveness);
}

void EngineTrailGenerator::update(float deltaSec) {
    if(m_engine.engineSlot()) { // Only spawn if engine is installed
        m_timeSinceLastSpawn += deltaSec;

        updateTrailSettings();

        if (m_engine.state().directional().z <= -0.05f) { //only when moving forward
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
    m_spawnOffset = m_creator.transform().scale() * 1.2f;

    glm::vec3 newPosition = calculateSpawnPosition();
    glm::vec3 distance = newPosition - m_lastSpawnPoint;
    glm::vec3 step = safeNormalize(distance) * prop_stepDistance.get();
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
    return m_engine.engineSlot()->voxel()->position() + m_creator.transform().orientation() * glm::vec3(0, 0, m_spawnOffset);
}

void EngineTrailGenerator::spawnAt(glm::vec3 position) {
    m_generator->setPosition(position);
    m_generator->setImpactVector(m_creator.transform().orientation() * (glm::vec3(0, 0, 0.1f) * glm::abs(m_creator.physics().acceleration().directional()) / 5.0f));

    m_generator->spawn();
    m_timeSinceLastSpawn = 0.0f;
    m_lastSpawnPoint = position;
}

/*
    The worldobject and therefore the radius and scale of the particles
    may change every frame, so the only way to really ensure safety here is to set
    them very frame
*/
void EngineTrailGenerator::updateTrailSettings() {
    const WorldObject* worldObject = m_engine.engineSlot()->components()->worldObject();

    m_generator->setScale(worldObject->transform().scale() / 15.0f);
    m_generator->setRadius(worldObject->transform().scale() * 0.3f);
}


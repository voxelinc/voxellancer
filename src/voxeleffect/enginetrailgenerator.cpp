#include "enginetrailgenerator.h"

#include "worldobject/components/engine.h"
#include "worldobject/worldobject.h"


EngineTrailGenerator::EngineTrailGenerator(Engine* engine) :
    m_generator(),
    m_engine(engine),
    m_worldObject(engine->engineSlot()->components()->worldObject()),
    m_spawnOffset(0.5f),
    m_lastPosition(),
    m_lastValid(false),
    m_timeSinceLastSpawn(0),
    prop_lifetime("vfx.engineTrailLifetime"),
    prop_stepDistance("vfx.engineTrailStepDistance"),
    prop_idleTime("vfx.engineTrailIdleCooldown")
{
    assert(engine != nullptr);

    m_spawnOffset = m_worldObject->transform().scale() * 0.75f;
    m_lastPosition = engine->position() + m_worldObject->transform().orientation() * glm::vec3(0, 0, m_spawnOffset);

    m_generator.setColor(0x6666FF);
    m_generator.setCount(8);
    m_generator.setForce(0.10f, 0.3f);
    m_generator.setLifetime(prop_lifetime, 0.1f);
    m_generator.setScale(m_worldObject->transform().scale() / 15.0f);
    m_generator.setRadius(m_worldObject->transform().scale() * 0.3f);
}

EngineTrailGenerator::~EngineTrailGenerator() {
}

void EngineTrailGenerator::update(float deltaSec) {
    assert(m_engine);

    glm::vec3 speedLocalSystem = glm::inverse(m_worldObject->transform().orientation()) * m_worldObject->physics().directionalSpeed();
    if (speedLocalSystem.z <= 0.5) { //only when not moving backwards
        if (!m_lastValid){
            m_lastPosition = calculateSpawnPosition();
            m_lastValid = true;
        }

        glm::vec3 newPosition = calculateSpawnPosition();
        glm::vec3 distance = newPosition - m_lastPosition;
        int stepCount = (int)glm::floor(glm::length(distance) / prop_stepDistance);
        if (stepCount != 0){
            glm::vec3 step = glm::normalize(distance) * prop_stepDistance.get();

            glm::vec3 currentPosition = m_lastPosition;
            for (int i = 0; i < stepCount; i++){
                currentPosition += step;

                spawnAt(currentPosition);
            }
        }
    } else {
        m_lastValid = false;
    }

    m_timeSinceLastSpawn += deltaSec;

    // When not moving, we still want some exhausts
    if (m_timeSinceLastSpawn > prop_idleTime) {
        spawnAt(calculateSpawnPosition());
    }
}

glm::vec3 EngineTrailGenerator::calculateSpawnPosition() {
    return m_engine->position() + m_worldObject->transform().orientation() * glm::vec3(0, 0, m_spawnOffset);
}

void EngineTrailGenerator::spawnAt(glm::vec3 position) {
    m_generator.setPosition(position);
    m_generator.setImpactVector(m_worldObject->transform().orientation() * (glm::vec3(0, 0, 0.1f) * glm::abs(m_worldObject->physics().directionalAcceleration()) / 5.0f));

    m_generator.spawn();
    m_timeSinceLastSpawn = 0.0f;
    m_lastPosition = position;
}


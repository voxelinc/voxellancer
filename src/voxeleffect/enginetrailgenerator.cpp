#include "enginetrailgenerator.h"

#include "worldobject/engine.h"
#include "worldobject/ship.h"


EngineTrailGenerator::EngineTrailGenerator() :
    m_generator(),
    m_engine(nullptr),
    m_frequency(1),
    m_spawnOffset(0.5f),
    m_lastPosition(),
    m_deltaSecLeft(0),
    prop_lifetime("vfx.engineTrailLifetime")
{
}

EngineTrailGenerator::~EngineTrailGenerator() {
}

void EngineTrailGenerator::setEngine(Engine* engine){
    assert(engine != nullptr);
    m_engine = engine;
    m_spawnOffset = m_engine->ship()->transform().scale() * 0.75f;
    m_lastPosition = engine->position() + m_engine->ship()->transform().orientation() * glm::vec3(0, 0, m_spawnOffset);

    m_generator.setColor(0x0000FF);
    m_generator.setDensity(2);
    m_generator.setForce(0.3f);
    m_generator.setLifetime(prop_lifetime, 0.1f);
    m_generator.setScale(m_engine->ship()->transform().scale() / 5.0f);
}

void EngineTrailGenerator::setFrequency(float frequency) {
    m_frequency = frequency;
}

void EngineTrailGenerator::update(float deltaSec){
    assert(m_engine);
    
    glm::vec3 speedLocalSystem = glm::inverse(m_engine->ship()->transform().orientation()) * m_engine->ship()->physics().speed();
    if (speedLocalSystem.z <= 0.5){ //only when not moving backwards
        float engineLoad = glm::length(m_engine->ship()->physics().acceleration()) / 20.0f; //TODO: ask the ship for maximum acceleration or engine load
        float cooldown = (1.0f / m_frequency) / (1 + engineLoad);

        float totalTime = deltaSec + m_deltaSecLeft;
        float currentTime = 0;
        glm::vec3 newPosition = m_engine->position() + m_engine->ship()->transform().orientation() * glm::vec3(0, 0, m_spawnOffset);
        glm::vec3 currentPosition = m_lastPosition;
        while (currentTime + cooldown < totalTime) {
            currentTime += cooldown;
            currentPosition = glm::mix(m_lastPosition, newPosition, currentTime / totalTime);

            m_generator.setPosition(currentPosition);
            m_generator.setOrientation(m_engine->ship()->transform().orientation());
            float impact = /*glm::length(m_worldObject->physics().acceleration()) +*/ 0.1f;
            m_generator.setImpactVector(m_engine->ship()->transform().orientation() * glm::vec3(0, 0, impact));

            m_generator.spawn();
        }
        m_lastPosition = currentPosition;
        m_deltaSecLeft = totalTime - currentTime;
    }
}
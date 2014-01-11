#include "enginetrailgenerator.h"

#include "worldobject/engine.h"
#include "worldobject/ship.h"


EngineTrailGenerator::EngineTrailGenerator() :
    m_generator(),
    m_frequency(1),
    m_cooldown(0),
    m_engine(nullptr),
    prop_lifetime("vfx.engineTrailLifetime")
{
}

EngineTrailGenerator::~EngineTrailGenerator() {
}

void EngineTrailGenerator::setEngine(Engine* engine){
    assert(engine != nullptr);
    m_engine = engine;

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
    
    m_cooldown -= deltaSec;
    if (m_cooldown < 0) {
        glm::vec3 speedLocalSystem = glm::inverse(m_engine->ship()->transform().orientation()) * m_engine->ship()->physics().speed();
        if (speedLocalSystem.z <= 0.5){ //only when not moving backwards
            float offset = m_engine->ship()->transform().scale() * 0.75f;
            m_generator.setPosition(m_engine->position() + m_engine->ship()->transform().orientation() * glm::vec3(0, 0, offset));
            m_generator.setOrientation(m_engine->ship()->transform().orientation());
            float impact = /*glm::length(m_worldObject->physics().acceleration()) +*/ 0.05f;
            m_generator.setImpactVector(m_engine->ship()->transform().orientation() * glm::vec3(0, 0, impact));

            m_generator.spawn();
            m_cooldown = 1.0f / m_frequency;
            if (glm::length(m_engine->ship()->physics().acceleration()) > 0.1f)
                m_cooldown /= (glm::length(m_engine->ship()->physics().acceleration()) / 10.0f);
        }
    }
}
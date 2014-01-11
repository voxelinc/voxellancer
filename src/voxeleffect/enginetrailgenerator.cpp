#include "enginetrailgenerator.h"

#include <GL/glew.h> //this is not needed but wants to be included befor gl.h which is included by glfw

#include <GLFW/glfw3.h>

#include "worldobject/engine.h"
#include "worldobject/ship.h"


EngineTrailGenerator::EngineTrailGenerator() :
    m_generator(),
    m_engine(nullptr),
    m_spawnOffset(0.5f),
    m_lastPosition(),
    m_lastValid(false),
    m_lastSpawn(0),
    prop_lifetime("vfx.engineTrailLifetime"),
    prop_stepDistance("vfx.engineTrailStepDistance"),
    prop_idleTime("vfx.engineTrailIdleCooldown")
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

void EngineTrailGenerator::update(float deltaSec){
    assert(m_engine);

    //this is neccessary to prevent a trail between origin and spawn-position
    if (!m_lastValid){
        m_lastPosition = calculateSpawnPosition();
        m_lastValid = true;
    }

    glm::vec3 speedLocalSystem = glm::inverse(m_engine->ship()->transform().orientation()) * m_engine->ship()->physics().speed();
    if (speedLocalSystem.z <= 0.5){ //only when not moving backwards
        glm::vec3 newPosition = calculateSpawnPosition();
        glm::vec3 distance = newPosition - m_lastPosition;
        int stepCount = (int)glm::floor(glm::length(distance) / prop_stepDistance);
        if (stepCount != 0){
            glm::vec3 step = glm::normalize(distance) * prop_stepDistance.get();

            glm::vec3 currentPosition = m_lastPosition;
            for (int i = 0; i < stepCount; i++){
                currentPosition += step;

                m_generator.setPosition(currentPosition);
                m_generator.setOrientation(m_engine->ship()->transform().orientation());
                m_generator.setImpactVector(m_engine->ship()->transform().orientation() * glm::vec3(0, 0, 0.1f));

                m_generator.spawn();
                m_lastSpawn = glfwGetTime();
            }
            m_lastPosition = currentPosition;
        }
    }

    // When not moving, we still want some exhausts
    if (glfwGetTime() - m_lastSpawn > prop_idleTime){
        m_generator.setPosition(calculateSpawnPosition());
        m_generator.setOrientation(m_engine->ship()->transform().orientation());
        m_generator.setImpactVector(m_engine->ship()->transform().orientation() * glm::vec3(0, 0, 0.1f));

        m_generator.spawn();
        m_lastSpawn = glfwGetTime();
    }
}

glm::vec3 EngineTrailGenerator::calculateSpawnPosition(){
    return m_engine->position() + m_engine->ship()->transform().orientation() * glm::vec3(0, 0, m_spawnOffset);
}
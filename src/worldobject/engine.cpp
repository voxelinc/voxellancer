#include "engine.h"

#include "ship.h"
#include "voxel/specialvoxels/enginevoxel.h"

Engine::Engine(EnginedWorldObject* worldObject, EngineVoxel* voxel) :
    m_generator(),
    prop_cooldownTime("vfx.engineTrailCooldownTime"),
    m_cooldown(0.0f)
{
    assert(worldObject != nullptr);
    m_worldObject = worldObject;
    m_positionInGrid = glm::vec3(voxel->gridCell());

    m_generator.setColor(voxel->color());
    m_generator.setDensity(2);
    m_generator.setForce(0.3f);
    m_generator.setLifetime(Property<float>("vfx.engineTrailLifetime"), 0.1f);
    m_generator.setScale(m_worldObject->transform().scale() / 5.0f);
}

Engine::~Engine() {
}

glm::vec3 Engine::position() {
    return m_worldObject->transform().applyTo(m_positionInGrid);
}

EnginedWorldObject* Engine::worldObject() {
    return m_worldObject;
}

void Engine::update(float deltaSec) {
    m_cooldown -= deltaSec;
    if (m_cooldown < 0) {
        glm::vec3 speedLocalSystem = glm::inverse(m_worldObject->transform().orientation()) * m_worldObject->physics().speed();
        if (speedLocalSystem.z <= 0.5){ //only when not moving backwards
            float offset = m_worldObject->transform().scale() * 0.75f;
            m_generator.setPosition(m_worldObject->transform().applyTo(m_positionInGrid + glm::vec3(0, 0, offset)));
            m_generator.setOrientation(m_worldObject->transform().orientation());
            float impact = /*glm::length(m_worldObject->physics().acceleration()) +*/ 0.05f;
            m_generator.setImpactVector(m_worldObject->transform().orientation() * glm::vec3(0, 0, impact));

            m_generator.spawn();
            m_cooldown = prop_cooldownTime;
            if (glm::length(m_worldObject->physics().acceleration()) > 0.1f)
                m_cooldown /= (glm::length(m_worldObject->physics().acceleration()) / 10.0f);
        }
    }
}

void Engine::voxelRemoved() {
    m_worldObject->removeEngine(this);
}


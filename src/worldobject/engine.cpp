#include "engine.h"

#include "ship.h"
#include "voxel/specialvoxels/enginevoxel.h"

Engine::Engine(Ship* ship, EngineVoxel* voxel) :
    m_generator(),
    prop_cooldownTime("vfx.engineTrailCooldownTime"),
    m_cooldown(0.0f)
{
    assert(ship != nullptr);
    m_ship = ship;
    m_positionInGrid = glm::vec3(voxel->gridCell());

    m_generator.setColor(voxel->color());
    m_generator.setDensity(1);
    m_generator.setForce(0.2f);
    m_generator.setLifetime(Property<float>("vfx.engineTrailLifetime"), 0.1f);
    m_generator.setScale(ship->transform().scale() / 5.0f);
}

Engine::~Engine() {
}

glm::vec3 Engine::position() {
    return m_ship->transform().applyTo(m_positionInGrid);
}

Ship* Engine::ship() {
    return m_ship;
}

void Engine::update(float deltaSec) {
    m_cooldown -= deltaSec;
    if (m_cooldown < 0) {
        glm::vec3 speedLocalSystem = glm::inverse(m_ship->transform().orientation()) * m_ship->physics().speed();
        if (speedLocalSystem.z <= 0.5){ //only when not moving backwards
            float offset = m_ship->transform().scale();
            m_generator.setPosition(m_ship->transform().applyTo(m_positionInGrid + glm::vec3(0, 0, offset)));
            m_generator.setOrientation(m_ship->transform().orientation());
            float impact = /*glm::length(m_ship->physics().speed()) / 10.0f +*/ 0.1f;
            m_generator.setImpactVector(m_ship->transform().orientation() * glm::vec3(0, 0, impact));

            m_generator.spawn();
            m_cooldown = prop_cooldownTime;
            if (glm::length(m_ship->physics().acceleration()) > 0.1f)
                m_cooldown /= (glm::length(m_ship->physics().acceleration()) / 10.0f);
        }
    }
}

void Engine::voxelRemoved() {
    m_ship->removeEngine(this);
}


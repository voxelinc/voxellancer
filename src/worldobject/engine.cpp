#include "engine.h"

#include "ship.h"
#include "voxel/specialvoxels/enginevoxel.h"

Engine::Engine(Ship* ship, EngineVoxel* voxel) :
    m_generator(),
    m_cooldown(0.0f)
{
    assert(ship != nullptr);
    m_ship = ship;
    m_positionInGrid = glm::vec3(voxel->gridCell());

    m_generator.setEngine(this);
    m_generator.setFrequency(Property<float>("vfx.engineTrailFrequency"));
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
    m_generator.update(deltaSec);
}

void Engine::voxelRemoved() {
    m_ship->removeEngine(this);
}


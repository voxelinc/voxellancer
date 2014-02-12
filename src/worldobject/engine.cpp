#include "engine.h"

#include "ship.h"
#include "voxel/specialvoxels/enginevoxel.h"
#include "voxeleffect/enginetrailgenerator.h"

Engine::Engine(Ship* ship, EngineVoxel* voxel) :
    m_generator(new EngineTrailGenerator()),
    m_cooldown(0.0f)
{
    assert(ship != nullptr);
    m_ship = ship;
    m_positionInGrid = glm::vec3(voxel->gridCell());

    m_generator->setEngine(this);
}

Engine::~Engine() {
}

glm::vec3 Engine::positionInGrid() const {
    return m_positionInGrid;
}

glm::vec3 Engine::position() const{
    return m_ship->transform().applyTo(m_positionInGrid);
}

Ship* Engine::ship() {
    return m_ship;
}

void Engine::update(float deltaSec) {
    m_generator->update(deltaSec);
}

void Engine::voxelRemoved() {
    m_ship->removeEngine(this);
}




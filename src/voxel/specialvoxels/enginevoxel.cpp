#include "enginevoxel.h"

#include "voxel/voxelcluster.h"
#include "worldobject/worldobject.h"
#include "worldobject/engine.h"

EngineVoxel::EngineVoxel(const glm::ivec3& gridCell, int color, float mass, float hp) :
    Voxel(gridCell, color, mass, hp),
    m_worldObject(nullptr),
    m_engine(nullptr)    
{
    m_emissiveness = 0.3f;
}

EngineVoxel::~EngineVoxel() {
}

void EngineVoxel::addToObject(WorldObject *object) {
    m_worldObject = object;
    object->addEngineVoxel(this);
}

void EngineVoxel::setEngine(Engine* engine) {
    m_engine = engine;
}

void EngineVoxel::onRemoval() {
    if (m_engine){
        m_engine->voxelRemoved();
        m_engine = nullptr;
    }
}

void EngineVoxel::onDestruction() {
    Voxel::onDestruction();
}

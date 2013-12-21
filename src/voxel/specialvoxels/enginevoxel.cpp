#include "enginevoxel.h"

#include "voxel/voxelcluster.h"
#include "worldobject/worldobject.h"

EngineVoxel::EngineVoxel(const glm::ivec3& gridCell, int color, float mass, float hp) :
    Voxel(gridCell, color, mass, hp),
    m_worldObject(nullptr)
{
}

EngineVoxel::~EngineVoxel() {
}

void EngineVoxel::addToObject(WorldObject *object){
    m_worldObject = object;
    object->addEngineVoxel(this);
}

void EngineVoxel::onRemoval(){
    //TODO: Tell my engine I'm gone
}

void EngineVoxel::onDestruction(){
    //TODO: explode
}

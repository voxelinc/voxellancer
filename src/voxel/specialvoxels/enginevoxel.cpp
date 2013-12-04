#include "enginevoxel.h"

#include "voxel/voxelcluster.h"
#include "worldobject/worldobject.h"

EngineVoxel::EngineVoxel(const glm::ivec3 &gridCell, int color, float mass, float hp) :
    Voxel(gridCell, color, mass, hp),
    m_object(nullptr)
{
}

EngineVoxel::~EngineVoxel() {
}

void EngineVoxel::addToObject(WorldObject *object){
    m_object = object;
    object->addVoxel(this);
}

void EngineVoxel::onDestruction(){
    //TODO: Tell my engine I'm gone
}

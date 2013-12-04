#include "hardpointvoxel.h"

#include "voxel/voxelcluster.h"
#include "worldobject/worldobject.h"

HardpointVoxel::HardpointVoxel(const glm::ivec3 &gridCell, int color, float mass, float hp) :
    Voxel(gridCell, color, mass, hp),
    m_object(nullptr)
{
}

HardpointVoxel::~HardpointVoxel() {
}

void HardpointVoxel::addToObject(WorldObject *object){
    m_object = object;
    object->addVoxel(this);
}

void HardpointVoxel::onDestruction(){
    //TODO: Tell my hardpoint I'm gone
}

#include "hardpointvoxel.h"

#include "voxel/voxelcluster.h"
#include "worldobject/worldobject.h"
#include "worldobject/hardpoint.h"

HardpointVoxel::HardpointVoxel(const glm::ivec3 &gridCell, int color, float mass, float hp) :
    Voxel(gridCell, color, mass, hp),
    m_hardpoint(nullptr)
{
}

HardpointVoxel::~HardpointVoxel() {
}

void HardpointVoxel::addToObject(WorldObject *object){
    object->addHardpointVoxel(this);
}

void HardpointVoxel::setHardpoint(Hardpoint* hardpoint){
    m_hardpoint = hardpoint;
}

void HardpointVoxel::onRemoval(){
    if (m_hardpoint)
        m_hardpoint->voxelRemoved();
}

void HardpointVoxel::onDestruction(){
    //Drop Ammo?
}

#include "cockpitvoxel.h"

#include "voxel/voxelcluster.h"
#include "worldobject/worldobject.h"

CockpitVoxel::CockpitVoxel(const glm::ivec3 &gridCell, const int &color, float mass, float hp) :
    Voxel(gridCell, color, mass, hp),
    m_object(nullptr)
{
}

CockpitVoxel::~CockpitVoxel() {
}

void CockpitVoxel::addToCluster(VoxelCluster *cluster){
    cluster->addVoxel(this);
}

void CockpitVoxel::addToObject(WorldObject *object){
    m_object = object;
    object->addVoxel(this);
}

void CockpitVoxel::onDestruction(){
    //TODO: Tell my cockpit I'm gone
}

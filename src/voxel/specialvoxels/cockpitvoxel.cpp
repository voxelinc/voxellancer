#include "cockpitvoxel.h"

#include "voxel/voxelcluster.h"
#include "worldobject/worldobject.h"

CockpitVoxel::CockpitVoxel(const glm::ivec3 &gridCell, int color, float mass, float hp) :
    Voxel(gridCell, color, mass, hp),
    m_object(nullptr)
{
}

CockpitVoxel::~CockpitVoxel() {
}

void CockpitVoxel::addToObject(WorldObject *object){
    m_object = object;
    object->addVoxel(this);
}

void CockpitVoxel::onDestruction(){
    //TODO: Tell my cockpit I'm gone
}

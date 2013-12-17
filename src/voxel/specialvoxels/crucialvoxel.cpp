#include "crucialvoxel.h"

#include "voxel/voxelcluster.h"
#include "worldobject/worldobject.h"

CrucialVoxel::CrucialVoxel(const glm::ivec3& gridCell, int color, float mass, float hp) :
    Voxel(gridCell, color, mass, hp),
    m_worldObject(nullptr)
{
}

CrucialVoxel::~CrucialVoxel() {
}

void CrucialVoxel::addToObject(WorldObject *object){
    m_worldObject = object;
    assert(object->crucialVoxel() == nullptr);
    object->addVoxel(this);
    object->setCrucialVoxel(m_gridCell);
}

void CrucialVoxel::onRemoval(){
    //TODO: Destroy ship / make wreckage?
}

void CrucialVoxel::onDestruction(){
}

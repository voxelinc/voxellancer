#include "crucialvoxel.h"

#include "property/property.h"

#include "voxel/voxelcluster.h"

#include "worldobject/worldobject.h"


CrucialVoxel::CrucialVoxel(const glm::ivec3& gridCell, int index):
    SpecialVoxel(gridCell, Property<uint32_t>("voxels.crucial.color"), index, Property<float>("voxels.crucial.mass"), Property<float>("voxels.crucial.hp"))
{
}

void CrucialVoxel::addToObject(WorldObject* worldObject){
    assert(worldObject->crucialVoxel() == nullptr);

    Voxel::addToObject(worldObject);
    worldObject->setCrucialVoxel(m_gridCell);
}

void CrucialVoxel::onRemoval(){
    //TODO: Destroy ship / make wreckage?
}

void CrucialVoxel::onDestruction(){
    Voxel::onDestruction();
}


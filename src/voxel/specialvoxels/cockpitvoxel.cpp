#include "cockpitvoxel.h"

#include "property/property.h"

#include "voxel/voxelcluster.h"

#include "worldobject/worldobject.h"


CockpitVoxel::CockpitVoxel(const glm::ivec3& gridCell, int index):
    SpecialVoxel(gridCell, index, Property<uint32_t>::get("voxels.cockpit.color"), Property<float>::get("voxels.cockpit.density"), Property<float>::get("voxels.cockpit.hp"))
{
}

CockpitVoxel::CockpitVoxel(const CockpitVoxel& other):
    SpecialVoxel(other)
{
}

void CockpitVoxel::addToObject(WorldObject* worldObject) {
    Voxel::addToObject(worldObject);
    worldObject->addCockpitVoxel(m_gridCell);
}

CockpitVoxel* CockpitVoxel::clone() const {
    return new CockpitVoxel(*this);
}


#include "cockpitvoxel.h"

#include "property/property.h"

#include "voxel/voxelcluster.h"

#include "worldobject/worldobject.h"


CockpitVoxel::CockpitVoxel(const glm::ivec3& cell, int index):
    SpecialVoxel(cell, index, Property<uint32_t>::get("voxels.cockpit.color"), Property<float>::get("voxels.cockpit.density"), Property<float>::get("voxels.cockpit.hp"))
{
}

void CockpitVoxel::addToObject(WorldObject* worldObject) {
    Voxel::addToObject(worldObject);
    worldObject->addCockpitVoxel(m_gridCell);
}

void CockpitVoxel::onRemoval() {
    //TODO: Tell my cockpit I'm gone
}

void CockpitVoxel::onDestruction() {
    Voxel::onDestruction();
    // Spawn dead pilot
}


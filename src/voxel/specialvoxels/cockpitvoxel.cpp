#include "cockpitvoxel.h"

#include "property/property.h"

#include "voxel/voxelcluster.h"

#include "worldobject/worldobject.h"


CockpitVoxel::CockpitVoxel(const glm::ivec3& gridCell, int index):
    SpecialVoxel(gridCell, index, Property<uint32_t>::get("voxels.cockpit.color"), Property<float>::get("voxels.cockpit.unscaledMass"), Property<float>::get("voxels.cockpit.hp"))
{
}

void CockpitVoxel::addToObject(WorldObject* worldObject) {
    Voxel::addToObject(worldObject);
}

void CockpitVoxel::onRemoval() {
    //TODO: Tell my cockpit I'm gone
}

void CockpitVoxel::onDestruction() {
    Voxel::onDestruction();
    // Spawn dead pilot
}


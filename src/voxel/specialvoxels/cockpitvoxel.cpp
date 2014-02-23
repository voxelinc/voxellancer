#include "cockpitvoxel.h"

#include "property/property.h"

#include "voxel/voxelcluster.h"

#include "worldobject/worldobject.h"


CockpitVoxel::CockpitVoxel(const glm::ivec3& gridCell, int index):
    SpecialVoxel(gridCell, index, Property<int>("voxels.cockpit.color"), Property<float>("voxels.cockpit.mass"), Property<float>("voxels.cockpit.hp"))
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


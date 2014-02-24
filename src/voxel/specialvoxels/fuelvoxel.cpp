#include "fuelvoxel.h"

#include "property/property.h"

#include "voxel/voxelcluster.h"

#include "worldobject/worldobject.h"


FuelVoxel::FuelVoxel(const glm::ivec3& gridCell, int index):
    SpecialVoxel(gridCell, index, Property<int>("voxels.fuel.color"), Property<float>("voxels.fuel.mass"), Property<float>("voxels.fuel.hp"))
{
}

void FuelVoxel::addToObject(WorldObject* worldObject) {
    SpecialVoxel::addToObject(worldObject);
}

void FuelVoxel::onRemoval() {

}

void FuelVoxel::onDestruction(const WorldObject* owner) {
    //TODO: explode more than default
    SpecialVoxel::onDestruction(owner);
}


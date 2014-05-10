#include "fuelvoxel.h"

#include "property/property.h"

#include "voxel/voxelcluster.h"
#include "voxel/voxeltree.h"
#include "voxel/voxeltreenode.h"

#include "worldobject/worldobject.h"

#include "voxeleffect/fuelvoxelexplosion.h"


FuelVoxel::FuelVoxel(const glm::ivec3& gridCell, int index):
    SpecialVoxel(gridCell, index, Property<uint32_t>::get("voxels.fuel.color"), Property<float>::get("voxels.fuel.density"), Property<float>::get("voxels.fuel.hp"))
{
}

void FuelVoxel::addToObject(WorldObject* worldObject) {
    Voxel::addToObject(worldObject);
}

float FuelVoxel::damageForwardingDestructionDamage() {
    return 10000000.0f;
}

void FuelVoxel::onRemoval() {

}

std::shared_ptr<VoxelExplosion> FuelVoxel::destructionExplosion(float /*energy*/) {
    return std::shared_ptr<VoxelExplosion>(new FuelVoxelExplosion(*this));
}


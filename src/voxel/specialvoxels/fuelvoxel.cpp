#include "fuelvoxel.h"

#include "property/property.h"

#include "voxel/voxelcluster.h"
#include "voxel/voxeltree.h"
#include "voxel/voxeltreenode.h"

#include "worldobject/worldobject.h"

#include "voxeleffect/voxelexplosiongenerator.h"


FuelVoxel::FuelVoxel(const glm::ivec3& gridCell, int index):
    SpecialVoxel(gridCell, index, Property<uint32_t>::get("voxels.fuel.color"), Property<float>::get("voxels.fuel.mass"), Property<float>::get("voxels.fuel.hp"))
{
}

void FuelVoxel::addToObject(WorldObject* worldObject) {
    Voxel::addToObject(worldObject);
}

float FuelVoxel::damageForwardingDestructionDamage() {
    return 100.0f;
}

void FuelVoxel::onRemoval() {

}

void FuelVoxel::onDestruction() {
    Voxel::onDestruction();

    WorldObject* worldObject = m_voxelTreeNode->voxelTree()->worldObject();
    // In addition to spawning debris, explode a little
    VoxelExplosionGenerator generator(worldObject);
    generator.setPosition(position());
    generator.setRadius(worldObject->transform().scale());
    generator.setScale(worldObject->transform().scale() / 2.0f);
    generator.setCount(30);
    generator.setEmissiveness(0.4f);
    generator.setColor(0xFF0000);
    generator.setForce(0.4f);
    generator.setLifetime(0.9f, 0.4f);

    generator.spawn();
}


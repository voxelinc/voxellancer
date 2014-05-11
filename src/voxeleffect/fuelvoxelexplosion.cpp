#include "fuelvoxelexplosion.h"

#include "display/rendering/visuals.h"

#include "voxel/voxel.h"
#include "voxel/voxeltree.h"
#include "voxel/voxeltreenode.h"

#include "worldobject/worldobject.h"

#include "voxelexplosiongenerator.h"


FuelVoxelExplosion::FuelVoxelExplosion(Voxel& voxel):
    VoxelExplosion(voxel)
{
}

FuelVoxelExplosion::~FuelVoxelExplosion() = default;

void FuelVoxelExplosion::onSpawn() {
    assert(voxel().voxelTreeNode());

    WorldObject* worldObject = voxel().voxelTreeNode()->voxelTree()->worldObject();
    assert(worldObject);

    VoxelExplosionGenerator generator(worldObject);
    generator.setPosition(voxel().position());
    generator.setRadius(worldObject->transform().scale());
    generator.setScale(worldObject->transform().scale() / 1.5f, 0.5f);
    generator.setCount(30);
    generator.setEmissiveness(1.2f);
    generator.setColor(0xFF0000);
    generator.setForce(3.0f, 0.6f);
    generator.setLifetime(1.0f, 1.0f);
    generator.spawn();

    generator.setScale(worldObject->transform().scale() / 3.0f, 0.5f);
    generator.setCount(10);
    generator.setEmissiveness(0.8f);
    generator.setColor(0xFF9900);
    generator.setForce(12.0f, 0.4f);
    generator.setLifetime(1.4f, 0.7f);
    generator.spawn();

    generator.setScale(worldObject->transform().scale() * 1.3f);
    generator.setCount(6);
    generator.setEmissiveness(1.8f);
    generator.setColor(0xFF3300);
    generator.setForce(100.0f, 0.4f);
    generator.setLifetime(2.4f, 0.7f);
    generator.spawn();
}


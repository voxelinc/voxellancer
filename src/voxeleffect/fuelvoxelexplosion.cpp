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
    generator.setScale(worldObject->transform().scale() / 2.0f);
    generator.setCount(30);
    generator.setEmissiveness(0.4f);
    generator.setColor(0xFF0000);
    generator.setForce(0.3f, 0.5f);
    generator.setLifetime(0.9f, 0.4f);

    generator.spawn();
}


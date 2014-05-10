#include "voxelshatterexplosion.h"

#include "display/rendering/visuals.h"

#include "voxel/voxel.h"
#include "voxel/voxeltree.h"
#include "voxel/voxeltreenode.h"

#include "worldobject/worldobject.h"

#include "voxeldebrisgenerator.h"


VoxelShatterExplosion::VoxelShatterExplosion(Voxel& voxel, float energy):
    VoxelExplosion(voxel),
    m_energy(energy)
{
}

VoxelShatterExplosion::~VoxelShatterExplosion() = default;

void VoxelShatterExplosion::onSpawn() {
    assert(voxel().voxelTreeNode());

    WorldObject* worldObject = voxel().voxelTreeNode()->voxelTree()->worldObject();
    assert(worldObject);

    VoxelDebrisGenerator generator(worldObject);
    generator.setOrientation(worldObject->transform().orientation());
    generator.setPosition(worldObject->transform().applyTo(glm::vec3(voxel().gridCell())));
    generator.setScale(worldObject->transform().scale() * 0.8, 0.2f);
    generator.setColor(voxel().visuals().color());
    generator.setEmissiveness(voxel().visuals().emissiveness());
    generator.setForce(0.0008f * m_energy + 4.0f, 0.5f);
    generator.setSpawnProbability(0.8f);
    generator.setLifetime(Property<float>("vfx.debrisLifetime"), 0.9f);
    generator.spawn();
}


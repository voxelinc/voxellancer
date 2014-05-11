#include "dummyexplosion.h"

#include "voxel/voxel.h"

#include "voxeleffect/voxelexplosiongenerator.h"


DummyExplosion::~DummyExplosion() = default;

void DummyExplosion::spawn(const glm::vec3& position) {
    VoxelExplosionGenerator generator(nullptr);

    generator.setPosition(position);
    generator.setRadius(1.0f);
    generator.setScale(1.0f);
    generator.setCount(30);
    generator.setEmissiveness(0.0f);
    generator.setColor(0xFF0080);
    generator.setForce(3.0f, 0.6f);
    generator.setLifetime(1.0f, 1.0f);

    generator.spawn();
}


#pragma once
#include <glm/glm.hpp>

#include "property/property.h"
#include "voxelparticlespawnbase.h"

class VoxelCluster;
class Transform;

class VoxelExplosionGenerator : public VoxelParticleSpawnBase {
public:
    VoxelExplosionGenerator(const VoxelCluster* creator);
    virtual ~VoxelExplosionGenerator();

    void setRadius(float radius);
    void setCount(int count);

    void spawn();

protected:
    float m_radius;
    int m_count;

    float createScale();
};

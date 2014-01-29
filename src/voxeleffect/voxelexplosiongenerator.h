#pragma once
#include <glm/glm.hpp>

#include "property/property.h"
#include "voxelparticlespawnbase.h"

class Transform;

class VoxelExplosionGenerator : public VoxelParticleSpawnBase {
public:
    VoxelExplosionGenerator();
    virtual ~VoxelExplosionGenerator();

    void setRadius(float radius);
    void setCount(int count);

    void spawn();

protected:
    float m_radius;
    int m_count;

    float createScale();
};

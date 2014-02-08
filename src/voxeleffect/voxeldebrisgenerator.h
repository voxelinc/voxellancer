#pragma once

#include <glm/glm.hpp>

#include "property/property.h"
#include "voxelparticlespawnbase.h"

class Transform;

class VoxelDebrisGenerator : public VoxelParticleSpawnBase {
public:
    VoxelDebrisGenerator();
    virtual ~VoxelDebrisGenerator();

    void setOrientation(const glm::quat& orientation);
    void setDensity(int density);
    void setSpawnProbability(float spawnProbability);

    void spawn();


protected:
    glm::quat m_orientation;
    int m_density;
    float m_spawnProbability;
    float m_particleBaseLifetime;

    float createScale();
};


#pragma once

#include <glm/glm.hpp>

#include "property/property.h"
#include "particlespawnbase.h"

class WorldTransform;

class DebrisGenerator : public ParticleSpawnBase
{
public:
    DebrisGenerator();
    virtual ~DebrisGenerator();

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


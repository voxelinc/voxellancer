#pragma once
#include <glm/glm.hpp>

#include "property/property.h"
#include "particlespawnbase.h"

class WorldTransform;

class ExplosionGenerator : public ParticleSpawnBase
{
public:
    ExplosionGenerator();
    virtual ~ExplosionGenerator();

    void setRadius(float radius);
    void setCount(int count);

    void spawn();

protected:
    float m_radius;
    int m_count;

    float createScale();
};

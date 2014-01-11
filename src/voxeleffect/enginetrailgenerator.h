#pragma once

#include <glm/glm.hpp>

#include "property/property.h"
#include "voxeleffect/voxelexplosiongenerator.h"

class Engine;

class EngineTrailGenerator
{
public:
    EngineTrailGenerator();
    virtual ~EngineTrailGenerator();

    void setEngine(Engine* engine);
    void setFrequency(float frequency);

    void update(float deltaSec);

protected:
    Engine* m_engine;
    VoxelExplosionGenerator m_generator;
    float m_frequency;
    float m_spawnOffset;

    float m_deltaSecLeft;
    glm::vec3 m_lastPosition;

    Property<float> prop_lifetime;
};


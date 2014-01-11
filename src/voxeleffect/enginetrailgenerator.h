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
    float m_cooldown;


    Property<float> prop_lifetime;
};


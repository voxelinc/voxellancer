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
    glm::vec3 calculateSpawnPosition();
    void spawnAt(glm::vec3 position);

    Engine* m_engine;
    VoxelExplosionGenerator m_generator;
    float m_spawnOffset;

    glm::vec3 m_lastPosition;
    bool m_lastValid;
    double m_lastSpawn;

    Property<float> prop_lifetime, prop_stepDistance, prop_idleTime;
};


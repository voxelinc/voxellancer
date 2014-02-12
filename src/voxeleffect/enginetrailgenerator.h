#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "property/property.h"


class Engine;
class VoxelExplosionGenerator;

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
    std::unique_ptr<VoxelExplosionGenerator> m_generator;

    glm::vec3 m_lastPosition;
    bool m_lastValid;
    double m_timeSinceLastSpawn;
    float m_spawnOffset;

    Property<float> prop_lifetime, prop_stepDistance, prop_idleTime;

    glm::vec3 calculateSpawnPosition();
    void spawnAt(glm::vec3 position);
};


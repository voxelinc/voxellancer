#pragma once

#include <glm/glm.hpp>

#include "property/property.h"
#include "voxeleffect/voxelexplosiongenerator.h"


class Engine;
class WorldObject;

class EngineTrailGenerator
{
public:
    EngineTrailGenerator(Engine* engine);

    void setLifetime(float lifetime);

    void update(float deltaSec);


protected:
    Engine* m_engine;
    VoxelExplosionGenerator m_generator;
    float m_spawnOffset;

    glm::vec3 m_lastSpawnPoint;
    bool m_lastValid;
    float m_stepRest;
    double m_timeSinceLastSpawn;

    Property<float> prop_stepDistance;
    Property<float> prop_idleTime;

    void spawnTrail();
    void updateTrailSettings();
    glm::vec3 calculateSpawnPosition();
    void spawnAt(glm::vec3 position);
};


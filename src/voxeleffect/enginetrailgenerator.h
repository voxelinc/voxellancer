#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "property/property.h"

class Engine;
class WorldObject;
class VoxelExplosionGenerator;

class EngineTrailGenerator
{
public:
    EngineTrailGenerator(Engine& engine, const WorldObject& creator);
    virtual ~EngineTrailGenerator();

    void setLifetime(float lifetime);
    void setColor(int color);
    void setEmissiveness(float emissiveness);

    void update(float deltaSec);


protected:
    const WorldObject& m_creator;
    const Engine& m_engine;
    std::unique_ptr<VoxelExplosionGenerator> m_generator;

    glm::vec3 m_lastSpawnPoint;
    bool m_lastValid;
    float m_stepRest;
    double m_timeSinceLastSpawn;
    float m_spawnOffset;

    Property<float> prop_stepDistance;
    Property<float> prop_idleTime;
    void spawnTrail();
    void updateTrailSettings();
    glm::vec3 calculateSpawnPosition();
    void spawnAt(glm::vec3 position);
};


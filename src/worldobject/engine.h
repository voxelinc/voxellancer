#pragma once

#include "voxel/voxelcluster.h"
#include "resource/clustercache.h"
#include "voxeleffect/voxelexplosiongenerator.h"

class Ship;
class EngineVoxel;

class Engine {
public:
    Engine(Ship* ship, EngineVoxel* voxel);
    ~Engine();

    glm::vec3 position(); // in world coordinates
    Ship* ship();

    void update(float deltaSec);

    void voxelRemoved();

private:
    Ship* m_ship;
    glm::vec3 m_positionInGrid;
    VoxelExplosionGenerator m_generator;
    Property<float> prop_cooldownTime;
    float m_cooldown;
};

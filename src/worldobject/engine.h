#pragma once

#include "voxel/voxelcluster.h"
#include "resource/clustercache.h"
#include "voxeleffect/enginetrailgenerator.h"

class Ship;
class EngineVoxel;

class Engine {
public:
    Engine(Ship* Ship, EngineVoxel* voxel);
    ~Engine();

    glm::vec3 position(); // in world coordinates
    Ship* ship();

    void update(float deltaSec);

    void voxelRemoved();

private:
    Ship* m_ship;
    glm::vec3 m_positionInGrid;
    EngineTrailGenerator m_generator;
    float m_cooldown;
};

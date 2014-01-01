#pragma once

#include "voxel/voxelcluster.h"
#include "resource/clustercache.h"
#include "voxeleffect/voxelexplosiongenerator.h"

class EnginedWorldObject;
class EngineVoxel;

class Engine {
public:
    Engine(EnginedWorldObject* worldObject, EngineVoxel* voxel);
    ~Engine();

    glm::vec3 position(); // in world coordinates
    EnginedWorldObject* worldObject();

    void update(float deltaSec);

    void voxelRemoved();

private:
    EnginedWorldObject* m_worldObject;
    glm::vec3 m_positionInGrid;
    VoxelExplosionGenerator m_generator;
    Property<float> prop_cooldownTime;
    float m_cooldown;
};

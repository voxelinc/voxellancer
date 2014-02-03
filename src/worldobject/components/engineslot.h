#pragma once

#include <glm/glm.hpp>

#include "worldobjectslot.h"


class Engine;
class EngineSlotVoxel;
class WorldObjectComponents;

/*
    Slot with interchangeable engines
*/
class EngineSlot: public WorldObjectSlot {
public:
    EngineSlot(WorldObjectComponents* components, EngineSlotVoxel* voxel);

    EngineSlotVoxel* voxel();

    const glm::vec3& direction();
    void setDirection(const glm::vec3& direction);

    Engine* engine();
    void setEngine(Engine* engine);

    void update(float deltaSec);

    void onVoxelRemoval();


protected:
    EngineSlotVoxel* m_voxel;
    glm::vec3 m_direction;

    Engine* m_engine;
};

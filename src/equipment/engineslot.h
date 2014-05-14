#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "worldobjectslot.h"


class Engine;
class EngineSlotVoxel;
class WorldObjectComponents;

/**
 *   Slot with interchangeable engines
 */
class EngineSlot: public WorldObjectSlot {
public:
    EngineSlot(WorldObjectComponents* components, EngineSlotVoxel* voxel);

    const EngineSlotVoxel* voxel() const;

    const glm::vec3& direction();
    void setDirection(const glm::vec3& direction);

    const std::shared_ptr<Engine>& engine();
    void setEngine(const std::shared_ptr<Engine>& engine);

    void update(float deltaSec);

    void onVoxelRemoval();


protected:
    EngineSlotVoxel* m_voxel;
    std::shared_ptr<Engine> m_engine;

    glm::vec3 m_direction;
};


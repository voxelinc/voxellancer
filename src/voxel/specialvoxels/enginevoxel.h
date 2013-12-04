#pragma once

#include "voxel/voxel.h"

class EngineVoxel : public Voxel {
public:
    EngineVoxel(const glm::ivec3 &gridCell, int color = 0xFFFFFF, float mass = 1.0f, float hp = 1.0f);
    ~EngineVoxel();

    virtual void addToObject(WorldObject* object);

    virtual void onDestruction();

protected:
    WorldObject* m_object;
};
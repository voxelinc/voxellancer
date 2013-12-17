#pragma once

#include "voxel/voxel.h"

class FuelVoxel : public Voxel {
public:
    FuelVoxel(const glm::ivec3& gridCell, int color = 0xFFFFFF, float mass = 1.0f, float hp = 1.0f);
    ~FuelVoxel();

    virtual void addToObject(WorldObject* object);

    virtual void onRemoval(); 
    virtual void onDestruction();

protected:
    WorldObject* m_worldObject;
};
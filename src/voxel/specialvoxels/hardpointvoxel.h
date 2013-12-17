#pragma once

#include "voxel/voxel.h"

class Hardpoint;

class HardpointVoxel : public Voxel {
public:
    HardpointVoxel(const glm::ivec3& gridCell, int color = 0xFFFFFF, float mass = 1.0f, float hp = 1.0f);
    ~HardpointVoxel();

    virtual void addToObject(WorldObject* object);
    void setHardpoint(Hardpoint* hardpoint);

    virtual void onRemoval(); 
    virtual void onDestruction();

protected:
    Hardpoint* m_hardpoint;
};
#pragma once

#include "voxel/voxel.h"

class CrucialVoxel : public Voxel {
public:
    CrucialVoxel(const glm::ivec3 &gridCell, int color = 0xFFFFFF, float mass = 1.0f, float hp = 1.0f);
    ~CrucialVoxel();

    virtual void addToObject(WorldObject* object);

    virtual void onRemoval(); 
    virtual void onDestruction();

protected:
    WorldObject* m_object;
};
#pragma once

#include "voxel/voxel.h"

class FuelVoxel : public Voxel {
public:
    FuelVoxel(const glm::ivec3 &gridCell, const int &color, float mass = 1.0f, float hp = 1.0f);
    ~FuelVoxel();

    virtual void addToCluster(VoxelCluster* cluster);
    virtual void addToObject(WorldObject* object);

    virtual void onDestruction();

protected:
    WorldObject* m_object;
};
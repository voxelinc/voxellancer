#pragma once

#include "voxelexplosion.h"


class FuelVoxelExplosion : public VoxelExplosion {
public:
    FuelVoxelExplosion(Voxel& voxel);
    ~FuelVoxelExplosion() override;


protected:
    void onSpawn() override;
};


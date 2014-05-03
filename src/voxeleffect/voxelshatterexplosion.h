#pragma once

#include "voxelexplosion.h"


class VoxelShatterExplosion : public VoxelExplosion {
public:
    VoxelShatterExplosion(Voxel& voxel, float energy);
    ~VoxelShatterExplosion() override;


protected:
    float m_energy;

    void onSpawn();
};


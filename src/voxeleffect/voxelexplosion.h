#pragma once


class Voxel;

class VoxelExplosion {
public:
    VoxelExplosion(Voxel& voxel);
    virtual ~VoxelExplosion();

    Voxel& voxel();

    void spawn();


protected:
    Voxel& m_voxel;

    virtual void onSpawn() = 0;
};


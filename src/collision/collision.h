#pragma once

#include "voxel/voxel.h"


class Collision
{
public:
    Collision(Voxel *voxelA, Voxel *voxelB);
    virtual ~Collision();

    Voxel *voxelA();
    const Voxel *voxelA() const;

    Voxel *voxelB();
    const Voxel *voxelB() const;

protected:
    Voxel *m_voxelA;
    Voxel *m_voxelB;
};


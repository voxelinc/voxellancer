#pragma once

#include "voxel/voxel.h"


class PhysicalVoxelCluster;

class PhysicalVoxel : public Voxel
{
public:
    PhysicalVoxel(PhysicalVoxelCluster *physicalVoxelCluster);

    PhysicalVoxelCluster *physicalVoxelCluster();
    const PhysicalVoxelCluster *physicalVoxelCluster() const;

    float hp() const;
    void setHp(float hp);

    float mass() const;
    void setMass(float mass);


protected:
    PhysicalVoxelCluster *m_physicalVoxelCluster;
    float m_hp;
    float m_mass;
};

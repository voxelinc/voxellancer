#pragma once

#include <string>

#include "equipment.h"


class Voxel;
class VoxelCluster;

class Healer : public Equipment {
public:
    Healer(const std::string& equipmentKey);
    virtual ~Healer();

    float healCountdown() const;

    VoxelCluster* voxelCluster();
    void setVoxelCluster(VoxelCluster* voxelCluster);

    virtual void update(float deltaSec);


protected:
    VoxelCluster* m_voxelCluster;
    float m_healCountdown;

    /*
        Voxels to be healed per second
    */
    virtual float healSpeed() = 0;

    Voxel* getNextRevivedVoxel();
};

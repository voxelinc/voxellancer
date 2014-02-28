#include "healer.h"

#include <string>

#include "voxel/voxel.h"
#include "voxel/voxelcluster.h"
#include "voxel/voxelgraveyard.h"
#include "voxel/voxelneighbourhelper.h"


Healer::Healer(const std::string& equipmentKey):
    Equipment(equipmentKey),
    m_voxelCluster(nullptr)
{

}

Healer::~Healer() {

}

float Healer::healCountdown() const {
    return m_healCountdown;
}

VoxelCluster* Healer::voxelCluster() {
    return m_voxelCluster;
}

void Healer::setVoxelCluster(VoxelCluster* voxelCluster) {
    m_voxelCluster = voxelCluster;
}

void Healer::update(float deltaSec) {
    if (!m_voxelCluster) {
        return;
    }

    float healSpeed = this->healSpeed() * deltaSec;

    if (m_healCountdown - healSpeed <= 0) {
        m_healCountdown = std::max(0.0f, m_healCountdown - healSpeed + 1.0f);

        Voxel* voxel = getNextRevivedVoxel();
        if (voxel) {
            m_voxelCluster->graveyard().revive(voxel);
        }
    } else {
        m_healCountdown -= healSpeed;
    }
}

Voxel* Healer::getNextRevivedVoxel() {
    VoxelNeighbourHelper neighbourHelper(m_voxelCluster, false);

    for (Voxel* voxel : m_voxelCluster->graveyard().voxels()) {
        if (neighbourHelper.hasNeighbour(voxel)) {
            return voxel;
        }
    }
    return nullptr;
}


#include "voxelclusterorphan.h"

void VoxelClusterOrphan::addVoxel(Voxel *voxel) {
    m_orphanedVoxels.push_back(voxel);
}

void VoxelClusterOrphan::addAllVoxels(VoxelClusterOrphan *orphanCluster) {
    m_orphanedVoxels.insert(m_orphanedVoxels.end(), orphanCluster->orphanedVoxels().begin(), orphanCluster->orphanedVoxels().end());
}

VoxelCluster *VoxelClusterOrphan::exVoxelCluster() {
    return m_exVoxelCluster;
}

void VoxelClusterOrphan::setExVoxelCluster(VoxelCluster *exVoxelCluster) {
    m_exVoxelCluster = exVoxelCluster;
}

glm::ivec3 VoxelClusterOrphan::gridLlf() const {
    assert(m_exVoxelCluster != nullptr);
    assert(m_orphanedVoxels.size() > 0);

    glm::ivec3 llf = static_cast<glm::ivec3>((*m_orphanedVoxels.begin())->gridCell());

    for(Voxel *voxel : m_orphanedVoxels) {
        llf = glm::min(static_cast<cvec3>(llf), voxel->gridCell());
    }
}

std::list<Voxel*> VoxelClusterOrphan::orphanedVoxels() {
    return m_orphanedVoxels;
}

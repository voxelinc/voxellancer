#include "voxelclusterorphan.h"

void VoxelClusterOrphan::addVoxel(Voxel *voxel) {
    m_orphanedVoxels.push_back(voxel);
}

void VoxelClusterOrphan::addAllVoxels(VoxelClusterOrphan *orphanCluster) {
    m_orphanedVoxels.insert(m_orphanedVoxels.end(), orphanCluster->orphanedVoxels().begin(), orphanCluster->orphanedVoxels().end());
}

WorldObject *VoxelClusterOrphan::exWorldObject() {
    return m_exWorldObject;
}

void VoxelClusterOrphan::setExWorldObject(WorldObject *exWorldObject) {
    m_exWorldObject = exWorldObject;
}

glm::ivec3 VoxelClusterOrphan::gridLlf() const {
    assert(m_exWorldObject != nullptr);
    assert(m_orphanedVoxels.size() > 0);

    glm::ivec3 llf = (*m_orphanedVoxels.begin())->gridCell();

    for(Voxel *voxel : m_orphanedVoxels) {
        llf = glm::min(llf, voxel->gridCell());
    }
    return llf;
}

std::list<Voxel*> VoxelClusterOrphan::orphanedVoxels() {
    return m_orphanedVoxels;
}

#include "splitter.h"


void Splitter::split(std::list<VoxelClusterOrphan*> &voxelClusterOrphans) {
    m_splitOffWorldObjects.clear();

    for(VoxelClusterOrphan *orphanCluster : voxelClusterOrphans) {
        VoxelCluster *voxelCluster = createVoxelClusterFromOrphan(orphanCluster);
        m_splitOffWorldObjects.push_back(voxelCluster);
        removeExtractedVoxelsFromEx(orphanCluster);
    }
}

std::list<WorldObject*> &Splitter::splitOffVoxelClusters() {
    return m_splitOffWorldObjects;
}

VoxelCluster *Splitter::createVoxelClusterFromOrphan(VoxelClusterOrphan *orphanCluster) {
    glm::ivec3 gridCellShift;
    VoxelCluster *voxelCluster;

    gridCellShift = orphanCluster->gridLlf();
    voxelCluster = new VoxelCluster(glm::vec3(0), orphanCluster->exWorldObject()->scale());

    for(Voxel *voxel : orphanCluster->orphanedVoxels()) {
        Voxel *voxelClone = new Voxel(voxel->gridCell() - static_cast<cvec3>(gridCellShift), voxel->color, voxel->mass());
        voxelCluster->addVoxel(voxelClone);
    }

   // voxelCluster->recalculateCenterAndMass(); TODO
    return voxelCluster;
}

void Splitter::removeExtractedVoxelsFromEx(VoxelClusterOrphan *orphanCluster) {
    for(Voxel *voxel : orphanCluster->orphanedVoxels()) {
        orphanCluster->exWorldObject()->removeVoxel(voxel->gridCell());
    }
}


#include "splitter.h"


void Splitter::split(std::list<VoxelClusterOrphan*> &voxelClusterOrphans) {
    m_splitOffVoxelClusters.clear();

    for(VoxelClusterOrphan *orphanCluster : voxelClusterOrphans) {
        VoxelCluster *voxelCluster = createVoxelClusterFromOrphan(orphanCluster);
        m_splitOffVoxelClusters.push_back(voxelCluster);
        removeExtractedVoxelsFromEx(orphanCluster);
    }
}

std::list<VoxelCluster*> &Splitter::splitOffVoxelClusters() {
    return m_splitOffVoxelClusters;
}

VoxelCluster *Splitter::createVoxelClusterFromOrphan(VoxelClusterOrphan *orphanCluster) {
    glm::ivec3 gridCellShift;
    VoxelCluster *voxelCluster;

    gridCellShift = orphanCluster->gridLlf();
    voxelCluster = new VoxelCluster(glm::vec3(0), orphanCluster->exVoxelCluster()->scale());

    for(Voxel *voxel : orphanCluster->orphanedVoxels()) {
        Voxel *voxelClone = voxel->clone();
        voxelClone->setGridCell(voxelClone->gridCell() - static_cast<cvec3>(gridCellShift));
        voxelCluster->addVoxel(*voxelClone); // TODO: pass pointers to voxelcluster, goddamnit. This one memoryleaks, of course
    }

   // voxelCluster->recalculateCenterAndMass(); TODO
    return voxelCluster;
}

void Splitter::removeExtractedVoxelsFromEx(VoxelClusterOrphan *orphanCluster) {
    for(Voxel *voxel : orphanCluster->orphanedVoxels()) {
        orphanCluster->exVoxelCluster()->removeVoxel(voxel->gridCell());
    }
}


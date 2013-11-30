#include "splitter.h"

#include "voxelclusterorphan.h"

#include "world/worldobject.h"
#include "voxel/voxel.h"

void Splitter::split(std::list<VoxelClusterOrphan*> &voxelClusterOrphans) {
    m_splitOffWorldObjects.clear();

    for(VoxelClusterOrphan *orphanCluster : voxelClusterOrphans) {
        WorldObject *worldObject = createWorldObjectFromOrphan(orphanCluster);
        m_splitOffWorldObjects.push_back(worldObject);
        removeExtractedVoxelsFromEx(orphanCluster);
    }
}

std::list<WorldObject*> &Splitter::splitOffWorldObjects() {
    return m_splitOffWorldObjects;
}

WorldObject *Splitter::createWorldObjectFromOrphan(VoxelClusterOrphan *orphanCluster) {
    glm::ivec3 gridCellShift;
    WorldObject *worldObject;

    worldObject = new WorldObject(orphanCluster->exWorldObject()->transform().scale());
    gridCellShift = orphanCluster->gridLlf();

    for(Voxel *voxel : orphanCluster->orphanedVoxels()) {
        Voxel *voxelClone = new Voxel(voxel->gridCell() - gridCellShift, voxel->color(), voxel->mass());
        worldObject->addVoxel(voxelClone);
    }

   // voxelCluster->recalculateCenterAndMass(); TODO
    return worldObject;
}

void Splitter::removeExtractedVoxelsFromEx(VoxelClusterOrphan *orphanCluster) {
    for(Voxel *voxel : orphanCluster->orphanedVoxels()) {
        orphanCluster->exWorldObject()->removeVoxel(voxel->gridCell());
    }
}


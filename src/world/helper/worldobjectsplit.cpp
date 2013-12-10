#include "worldobjectsplit.h"

void WorldObjectSplit::addVoxel(Voxel *voxel) {
    m_splitOffVoxels.push_back(voxel);
}

void WorldObjectSplit::addAllVoxels(WorldObjectSplit *split) {
    m_splitOffVoxels.insert(m_splitOffVoxels.end(), split->splitOffVoxels().begin(), split->splitOffVoxels().end());
}

WorldObject *WorldObjectSplit::exWorldObject() {
    return m_exWorldObject;
}

void WorldObjectSplit::setExWorldObject(WorldObject *exWorldObject) {
    m_exWorldObject = exWorldObject;
}

std::list<Voxel*> WorldObjectSplit::splitOffVoxels() {
    return m_splitOffVoxels;
}

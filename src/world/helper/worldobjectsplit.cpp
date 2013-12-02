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

glm::ivec3 WorldObjectSplit::gridLlf() const {
    assert(m_exWorldObject != nullptr);
    assert(m_splitOffVoxels.size() > 0);

    glm::ivec3 llf = (*m_splitOffVoxels.begin())->gridCell();

    for(Voxel *voxel : m_splitOffVoxels) {
        llf = glm::min(llf, voxel->gridCell());
    }
    return llf;
}

std::list<Voxel*> WorldObjectSplit::splitOffVoxels() {
    return m_splitOffVoxels;
}

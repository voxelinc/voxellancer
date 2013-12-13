#include "worldobjectsplit.h"


WorldObjectSplit::WorldObjectSplit():
    m_exWorldObject(nullptr),
    m_llf(std::numeric_limits<int>::max())
{

}


void WorldObjectSplit::addVoxel(Voxel *voxel) {
    m_splitOffVoxels.push_back(voxel);
    m_llf = glm::min(m_llf, voxel->gridCell());
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

glm::ivec3 WorldObjectSplit::llf() {
    return m_llf;
}

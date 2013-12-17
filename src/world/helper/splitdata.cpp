#include "splitdata.h"


SplitData::SplitData():
    m_exWorldObject(nullptr),
    m_llf(std::numeric_limits<int>::max())
{

}


void SplitData::addVoxel(Voxel *voxel) {
    m_splitOffVoxels.push_back(voxel);
    m_llf = glm::min(m_llf, voxel->gridCell());
}

WorldObject *SplitData::exWorldObject() {
    return m_exWorldObject;
}

void SplitData::setExWorldObject(WorldObject *exWorldObject) {
    m_exWorldObject = exWorldObject;
}

std::list<Voxel*> SplitData::splitOffVoxels() {
    return m_splitOffVoxels;
}

glm::ivec3 SplitData::llf() {
    return m_llf;
}

#include "splitdata.h"
#include "voxel/voxel.h"


SplitData::SplitData(WorldObject* worldObject):
    m_exWorldObject(worldObject),
    m_llf(std::numeric_limits<int>::max()),
    m_splitOffVoxels()
{

}

void SplitData::addVoxel(Voxel *voxel) {
    m_splitOffVoxels.push_back(voxel);
    m_llf = glm::min(m_llf, voxel->gridCell());
}

WorldObject *SplitData::exWorldObject() {
    return m_exWorldObject;
}

std::vector<Voxel*> SplitData::splitOffVoxels() {
    return m_splitOffVoxels;
}

glm::ivec3 SplitData::llf() {
    return m_llf;
}

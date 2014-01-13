#include "splitdetector_fill.h"

#include <limits>

#include "world/helper/splitdata.h"

#include "voxel/voxel.h"
#include "voxel/voxelneighbourhelper.h"

#include "worldobject/worldobject.h"


void SplitDetectorFill::searchSplitOffs(std::list<WorldObjectModification>& worldObjectModifications) {
    clear();

    for (WorldObjectModification& worldObjectModification : worldObjectModifications) {
        WorldObject* currentWorldObject = worldObjectModification.worldObject();
        if (currentWorldObject->voxelMap().size() > 1) {
            findSplits(currentWorldObject);
        }
    }
    
}


void SplitDetectorFill::findSplits(WorldObject* worldObject)
{
    init(worldObject);

    for (int z = 0; z < m_size.z; z++) {
        for (int y = 0; y < m_size.y; y++) {
            for (int x = 0; x < m_size.x; x++) {
                VoxelGroup& v = voxelGroup(x, y, z);
                if (v.voxel != nullptr && v.groupId == UNKNOWN) {
                    searchGroupId(x, y, z);
                }
            }
        }
    }

    mergeGroups();

    createSplitData(worldObject);

}


void SplitDetectorFill::init(WorldObject* worldObject)
{
    m_llf = worldObject->gridAABB().llf();
    m_size = worldObject->gridAABB().rub() - m_llf + glm::ivec3(1);

    m_voxelArray.clear();
    m_voxelArray.resize(m_size.x * m_size.y * m_size.z + 1);

    m_xy = m_size.y*m_size.x;
    m_x = m_size.x;

    for each (auto pair in worldObject->voxelMap())
    {
        glm::ivec3 pos = pair.second->gridCell() - m_llf;
        int index = address(pos);
        m_voxelArray[index].voxel = pair.second;
    }
    m_nextGroupId = 0;
}


void SplitDetectorFill::searchGroupId(int x, int y, int z)
{
    VoxelGroup& v = voxelGroup(x, y, z);
    if (v.voxel == nullptr){
        return;
    }
    v.groupId = getNeighbourGroupId(x, y, z);
}

void SplitDetectorFill::mergeGroups()
{
    m_groupMapping.resize(m_nextGroupId);

    for (int i = 0; i < m_nextGroupId; i++)
    {
        m_groupMapping[i] = i;
    }

    for (int z = 0; z < m_size.z; z++) {
        for (int y = 0; y < m_size.y; y++) {
            for (int x = 0; x < m_size.x; x++) {
                VoxelGroup& v = voxelGroup(x, y, z);
                if (v.voxel != nullptr) {
                    int m = getMinNeighbourGroupId(x, y, z, v.groupId);
                    if (v.groupId != m){
                        m_groupMapping[v.groupId] = glm::min(v.groupId, m);
                    }
                }
            }
        }
    }

    for (int i = 0; i < m_nextGroupId; i++)
    {
        m_groupMapping[i] = minMapping(i);
    }
}

int SplitDetectorFill::minMapping(int i)
{
    if (m_groupMapping[i] == i)
        return i;
    return minMapping(m_groupMapping[i]);
}


int SplitDetectorFill::getMinNeighbourGroupId(int x, int y, int z, int id) {
    int minId =
        glm::min(groupId(x - 1, y, z),
        glm::min(groupId(x, y - 1, z),
        glm::min(groupId(x, y, z - 1),
        glm::min(groupId(x - 1, y - 1, z),
        glm::min(groupId(x - 1, y, z - 1),
        glm::min(groupId(x, y - 1, z - 1),
        
        glm::min(groupId(x + 1, y - 1, z),
        glm::min(groupId(x + 1, y, z - 1),
        glm::min(groupId(x + 1, y - 1, z - 1), id
        )))))))));
        
    return minId;
}

void SplitDetectorFill::createSplitData(WorldObject* worldObject)
{
    m_splitDataList.resize(m_nextGroupId);
    for (int i = 0; i < m_nextGroupId; i++)
    {
        m_splitDataList[i] = new SplitData();
    }

    int crucialVoxelGroup = 0;
    Voxel* v = worldObject->crucialVoxel();
    if (v) {
        crucialVoxelGroup = m_voxelArray[address(v->gridCell() - m_llf)].groupId;
    }

    for each (VoxelGroup v in m_voxelArray)
    {
        if (v.voxel && v.groupId != crucialVoxelGroup) {
            assert(v.groupId != UNKNOWN);
            m_splitDataList[v.groupId]->addVoxel(v.voxel);
        }
    }

    if (crucialVoxelGroup > 0) {
        m_splitDataList.erase(m_splitDataList.begin() + crucialVoxelGroup);
    } else {
        m_splitDataList.erase(m_splitDataList.begin() + 1);
    }

    m_splitDataList.erase(m_splitDataList.begin());
}


int SplitDetectorFill::getNeighbourGroupId(int x, int y, int z) {
    int id =
        groupId(x - 1, y, z) ||
        groupId(x, y - 1, z) ||
        groupId(x, y, z - 1) ||
        groupId(x - 1, y - 1, z) ||
        groupId(x - 1, y, z - 1) ||
        groupId(x, y - 1, z - 1) ||
        m_nextGroupId++;
    return id;
}

int SplitDetectorFill::groupId(int x, int y, int z) {
    if (x < 0 || y < 0 || z < 0){
        return UNKNOWN;
    }
    return voxelGroup(x, y, z).groupId;
}

int SplitDetectorFill::address(glm::ivec3 &pos)
{
    return pos.z * m_xy + pos.y * m_x + pos.x;
}

VoxelGroup& SplitDetectorFill::voxelGroup(int x, int y, int z)
{
    int index = z * m_xy + y * m_x + x;
    return m_voxelArray[index];
}

std::vector<SplitData*> &SplitDetectorFill::splitDataList() {
    return m_splitDataList;
}

void SplitDetectorFill::clear() {
    for(SplitData *split : m_splitDataList) {
        delete split;
    }

    m_splitDataList.clear();
}




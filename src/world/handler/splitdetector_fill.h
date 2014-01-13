#pragma once

#include <list>
#include <vector>
#include <limits>

#include "world/helper/worldobjectmodification.h"


class SplitData;
class WorldObject;
class Voxel;

static int UNKNOWN = std::numeric_limits<int>::max(); 

struct VoxelGroup {
    VoxelGroup(): voxel(nullptr), groupId(UNKNOWN) { }
    Voxel* voxel;
    int groupId;
};


class SplitDetectorFill
{
public:
    void searchSplitOffs(std::list<WorldObjectModification>& worldObjectModifications);

    std::vector<SplitData*> &splitDataList();


protected:
    std::vector<SplitData*> m_splitDataList;
    std::vector<VoxelGroup> m_voxelArray;
    std::vector<int> m_groupMapping;
    int m_xy;
    int m_x;
    glm::ivec3 m_llf;
    glm::ivec3 m_size;
    int m_nextGroupId;

    void clear();
    void findSplits(WorldObject* worldObject);

    void createSplitData(WorldObject* worldObject);

    void init(WorldObject* worldObject);

    int address(glm::ivec3 &pos);
    VoxelGroup& voxelGroup(int x, int y, int z);
    void searchGroupId(int x, int y, int z);
    int getNeighbourGroupId(int x, int y, int z);
    int groupId(int x, int y, int z);
    int getMinNeighbourGroupId(int x, int y, int z, int id);
    void mergeGroups();
    int minMapping(int i);
};


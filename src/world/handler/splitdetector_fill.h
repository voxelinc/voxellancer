#pragma once

#include <list>
#include <vector>
#include <limits>

#include "world/helper/worldobjectmodification.h"
#include <stack>


class SplitData;
class WorldObject;
class Voxel;

static int UNKNOWN = 0;
static int VISITED = -1;

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
    std::stack<glm::ivec3> m_stack;
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
    VoxelGroup* voxelGroup(glm::ivec3 &pos);
    void fillColor(glm::ivec3& start, int groupId);
    void visit(glm::ivec3& p);
};


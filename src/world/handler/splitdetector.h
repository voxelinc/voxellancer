#pragma once

#include <list>
#include <vector>
#include <memory>
#include <limits>

#include "world/helper/worldobjectmodification.h"
#include <stack>


class SplitData;
class WorldObject;
class Voxel;


class SplitDetector
{
public:
    void searchSplitOffs(std::list<WorldObjectModification>& worldObjectModifications);

    std::vector<std::shared_ptr<SplitData>> &splitDataList();

protected:
    struct VoxelGroup {
        VoxelGroup();
        Voxel* voxel;
        int groupId;
    };
    
    std::vector<std::shared_ptr<SplitData>> m_splitDataList;
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

    int address(const glm::ivec3& pos);
    VoxelGroup* voxelGroup(const glm::ivec3& pos);
    void fillColor(const glm::ivec3& start, int groupId);
    void visit(const glm::ivec3& p);
};


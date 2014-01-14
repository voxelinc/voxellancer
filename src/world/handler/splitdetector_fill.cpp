#include "splitdetector_fill.h"

#include <limits>

#include "world/helper/splitdata.h"

#include "voxel/voxel.h"
#include "voxel/voxelneighbourhelper.h"

#include "worldobject/worldobject.h"


static const int FIRST_GROUP = 0;
static const int VISITED = -1;
static const int UNKNOWN = -2;


SplitDetectorFill::VoxelGroup::VoxelGroup():
    voxel(nullptr),
    groupId(UNKNOWN) 
{
}


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
                VoxelGroup* v = voxelGroup(glm::ivec3(x,y,z));
                if (v->voxel != nullptr && v->groupId == UNKNOWN) {
                    fillColor(glm::ivec3(x,y,z), m_nextGroupId++);
                }
            }
        }
    }

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

    for (auto& pair : worldObject->voxelMap())
    {
        glm::ivec3 pos = pair.second->gridCell() - m_llf;
        int index = address(pos);
        m_voxelArray[index].voxel = pair.second;
    }
    m_nextGroupId = FIRST_GROUP;
}

void SplitDetectorFill::fillColor(const glm::ivec3& start, int color)
{
    assert(m_stack.empty());

    m_stack.push(start);

    while (!m_stack.empty()) {
        glm::ivec3 p = m_stack.top();
        m_stack.pop();
        VoxelGroup* v = voxelGroup(p);

        if (v->groupId < FIRST_GROUP) {
            v->groupId = color;
        
            visit(glm::ivec3(p.x + 1, p.y + 1, p.z));
            visit(glm::ivec3(p.x - 1, p.y + 1, p.z));
            visit(glm::ivec3(p.x + 1, p.y - 1, p.z));
            visit(glm::ivec3(p.x - 1, p.y - 1, p.z));
            visit(glm::ivec3(p.x + 1, p.y, p.z - 1));
            visit(glm::ivec3(p.x - 1, p.y, p.z - 1));
            visit(glm::ivec3(p.x, p.y - 1, p.z - 1));
            visit(glm::ivec3(p.x, p.y + 1, p.z - 1));
            visit(glm::ivec3(p.x, p.y - 1, p.z + 1));
            visit(glm::ivec3(p.x, p.y + 1, p.z + 1));
            visit(glm::ivec3(p.x + 1, p.y, p.z + 1));
            visit(glm::ivec3(p.x - 1, p.y, p.z + 1));

            visit(glm::ivec3(p.x, p.y, p.z - 1));
            visit(glm::ivec3(p.x, p.y, p.z + 1));
            visit(glm::ivec3(p.x, p.y - 1, p.z));
            visit(glm::ivec3(p.x, p.y + 1, p.z));
            visit(glm::ivec3(p.x - 1, p.y, p.z));
            visit(glm::ivec3(p.x + 1, p.y, p.z));
        }
    }
}


void SplitDetectorFill::visit(const glm::ivec3& p) {
    if (p.x < 0 || p.y < 0 || p.z < 0 || p.x >= m_size.x || p.y >= m_size.y || p.z >= m_size.z){
        return;
    }
    VoxelGroup* v = voxelGroup(p);
    if (v->voxel == nullptr || v->groupId != UNKNOWN) {
        return;
    }
    static int counter;
    counter++;
    v->groupId = VISITED;
    m_stack.push(p);
}


void SplitDetectorFill::createSplitData(WorldObject* worldObject)
{
    m_splitDataList.resize(m_nextGroupId);
    for (int i = 0; i < m_nextGroupId; i++)
    {
        m_splitDataList[i] = new SplitData(worldObject);
    }

    int crucialVoxelGroup = 0;
    Voxel* v = worldObject->crucialVoxel();
    if (v) {
        crucialVoxelGroup = m_voxelArray[address(v->gridCell() - m_llf)].groupId;
    }

    for (const VoxelGroup& v : m_voxelArray)
    {
        if (v.voxel && v.groupId != crucialVoxelGroup) {
            assert(v.groupId != UNKNOWN);
            m_splitDataList[v.groupId]->addVoxel(v.voxel);
        }
    }

    if (crucialVoxelGroup > 0) {
        m_splitDataList.erase(m_splitDataList.begin() + crucialVoxelGroup);
    } else {
        m_splitDataList.erase(m_splitDataList.begin());
    }
}


int SplitDetectorFill::address(const glm::ivec3 &pos)
{
    return pos.z * m_xy + pos.y * m_x + pos.x;
}

SplitDetectorFill::VoxelGroup* SplitDetectorFill::voxelGroup(const glm::ivec3& p)
{
    return &m_voxelArray[address(p)];
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


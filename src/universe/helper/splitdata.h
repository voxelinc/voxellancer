#pragma once

#include <vector>

#include <glm/glm.hpp>

class WorldObject;
class Voxel;


class SplitData
{
public:
    SplitData(WorldObject* worldObject);
    
    void addVoxel(Voxel *voxel);

    WorldObject *exWorldObject();

    std::vector<Voxel*> splitOffVoxels();
    glm::ivec3 llf();

protected:
    WorldObject* m_exWorldObject;
    std::vector<Voxel*> m_splitOffVoxels;
    glm::ivec3 m_llf;
};


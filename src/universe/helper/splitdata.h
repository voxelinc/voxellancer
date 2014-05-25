#pragma once

#include <vector>

#include <glm/glm.hpp>

#include <glow/ref_ptr.h>


class WorldObject;
class Voxel;

class SplitData {
public:
    SplitData(WorldObject* worldObject);

    void addVoxel(Voxel *voxel);

    WorldObject *exWorldObject();

    std::vector<Voxel*> splitOffVoxels();
    glm::ivec3 llf();

protected:
    glow::ref_ptr<WorldObject> m_exWorldObject;
    std::vector<Voxel*> m_splitOffVoxels;
    glm::ivec3 m_llf;
};


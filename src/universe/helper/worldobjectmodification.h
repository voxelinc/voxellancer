#pragma once

#include <vector>

#include <glm/glm.hpp>


class WorldObject;

class WorldObjectModification
{
public:
    WorldObjectModification(WorldObject *worldObject);

    WorldObject *worldObject();

    void removedVoxel(const glm::ivec3 &pos);
    const std::vector<glm::ivec3> &removedVoxels();


protected:
    WorldObject *m_worldObject;
    std::vector<glm::ivec3> m_removedVoxels;
};

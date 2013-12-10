#include "worldobjectmodification.h"

WorldObjectModification::WorldObjectModification(WorldObject *worldObject):
    m_worldObject(worldObject)
{

}

WorldObject *WorldObjectModification::worldObject() {
    return m_worldObject;
}

void WorldObjectModification::removedVoxel(const glm::ivec3 &pos) {
    m_removedVoxels.push_back(pos);
}

const std::vector<glm::ivec3> &WorldObjectModification::removedVoxels() {
    return m_removedVoxels;
}

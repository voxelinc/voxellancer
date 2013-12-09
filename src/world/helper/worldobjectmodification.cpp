#include "worldobjectmodification.h"

WorldObjectModification::WorldObjectModification(WorldObject *worldObject):
    m_worldObject(worldObject)
{

}

WorldObject *WorldObjectModification::worldObject() {
    return m_worldObject;
}

void WorldObjectModification::cellCleared(const glm::ivec3 &cell) {
    m_clearedCells.push_back(cell);
}

const std::list<glm::ivec3> &WorldObjectModification::clearedCells() {
    return m_clearedCells;
}

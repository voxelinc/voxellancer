#pragma once

#include <list>

#include <glm/glm.hpp>


class WorldObject;

class WorldObjectModification
{
public:
    WorldObjectModification(WorldObject *worldObject);

    WorldObject *worldObject();

    void cellCleared(const glm::ivec3 &cell);
    const std::list<glm::ivec3> &clearedCells();


protected:
    WorldObject *m_worldObject;
    std::list<glm::ivec3> m_clearedCells;
};

#pragma once

#include <list>

class WorldObject;
class World;

class God
{
public:
    God(World& world);
    virtual ~God();

    void scheduleSpawn(WorldObject *worldObject);
    void scheduleSpawns(const std::list<WorldObject*> &spawns);
    const std::list<WorldObject*> scheduledSpawns();

    void scheduleRemoval(WorldObject *worldObject);
    void scheduleRemovals(const std::list<WorldObject*> &removals);
    const std::list<WorldObject*> scheduledRemovals();

    void spawn();
    void remove();


protected:
    World & m_world;
    std::list<WorldObject*> m_scheduledSpawns;
    std::list<WorldObject*> m_scheduledRemovals;
};

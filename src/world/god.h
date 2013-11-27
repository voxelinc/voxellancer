#pragma once

#include <list>

class WorldObject;
class World;

class God
{
public:
    God(World & world);
    virtual ~God();

    void scheduleSpawn(WorldObject *cluster);
    void scheduleSpawns(const std::list<WorldObject*> &spawns);
    void scheduleRemoval(WorldObject *cluster);
    void scheduleRemovals(const std::list<WorldObject*> &removals);

    void spawn();
    void remove();
protected:
    World & m_world;
    std::list<WorldObject*> m_scheduledSpawns;
    std::list<WorldObject*> m_scheduledRemovals;
};

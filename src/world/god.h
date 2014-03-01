#pragma once

#include <list>

class WorldObject;
class World;

/*
    Responsible for safely inserting object into the World, preventing overlappings
    * to spawn an object, first call scheduleSpawn() and then spawn()
    * to remove an object, first call scheduleRemoval and then remove()
*/
class God {
public:
    God(World& world);
    virtual ~God();

    void scheduleSpawn(WorldObject *worldObject);
    void scheduleSpawns(const std::list<WorldObject*> &spawns);
    const std::list<WorldObject*>& scheduledSpawns();

    void scheduleRemoval(WorldObject *worldObject);
    void scheduleRemovals(const std::list<WorldObject*> &removals);
    const std::list<WorldObject*>& scheduledRemovals();

    void spawn();
    void remove();


protected:
    World & m_world;
    std::list<WorldObject*> m_scheduledSpawns;
    std::list<WorldObject*> m_scheduledRemovals;
};

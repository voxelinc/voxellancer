#pragma once

#include <list>

#include "spawnrequest.h"


class WorldObject;
class World;

/**
*    Responsible for safely inserting object into the World, preventing overlappings
*    * to spawn an object, first call scheduleSpawn() and then spawn()
*    * to remove an object, first call scheduleRemoval and then remove()
*
*    The World will be given full ownership of spawned object, rejected objects however
*    will have to be managed by the caller.
*/
class God {
public:
    God(World& world);
    virtual ~God();

    void scheduleSpawn(SpawnRequest spawnRequest);

    void scheduleRemoval(WorldObject *worldObject);
    void scheduleRemovals(const std::list<WorldObject*> &removals);

    void spawn();
    void remove();


protected:
    World & m_world;
    std::list<SpawnRequest> m_spawnRequests;
    std::list<WorldObject*> m_scheduledRemovals;
};

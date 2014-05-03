#pragma once

#include <list>


class WorldObject;

/**
 * Encapsulates the request to &God to spawn a number of &WorldObject into
 * the &World
 * Currently available metadata is:
 * -> deleteOnRejection: Controls whether the object is deleted when it can't be spawned
 */
class SpawnRequest {
public:
    SpawnRequest(WorldObject* worldObject, bool deleteOnRejection = true);
    SpawnRequest(const std::list<WorldObject*>& worldObjects, bool deleteOnRejection = true);

    std::list<WorldObject*>& worldObjects();
    bool deleteOnRejection() const;


protected:
    std::list<WorldObject*> m_worldObjects;
    bool m_deleteOnRejection;
};


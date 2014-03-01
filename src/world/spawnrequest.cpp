#include "spawnrequest.h"

SpawnRequest::SpawnRequest(WorldObject* worldObject, bool deleteOnRejection):
    m_worldObjects({worldObject}),
    m_deleteOnRejection(deleteOnRejection)
{

}

SpawnRequest::SpawnRequest(const std::list<WorldObject*>& worldObjects, bool deleteOnRejection):
    m_worldObjects(worldObjects),
    m_deleteOnRejection(deleteOnRejection)
{

}

std::list<WorldObject*>& SpawnRequest::worldObjects() {
    return m_worldObjects;
}

bool SpawnRequest::deleteOnRejection() const {
    return m_deleteOnRejection;
}

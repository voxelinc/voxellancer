#include "worldobjecthandle.h"

#include <assert.h>


WorldObjectHandle::WorldObjectHandle(WorldObject* worldObject) :
    m_worldObject(worldObject)
{
}

void WorldObjectHandle::invalidate() {
    m_worldObject = nullptr;
}

WorldObject* WorldObjectHandle::get() {
    return m_worldObject;
}


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

std::shared_ptr<WorldObjectHandle> WorldObjectHandle::nullHandle() {
    if (s_nullInstance == nullptr)
        s_nullInstance = std::shared_ptr<WorldObjectHandle>(new WorldObjectHandle(nullptr));
    return s_nullInstance;
}

std::shared_ptr<WorldObjectHandle> WorldObjectHandle::s_nullInstance;


#include "worldobjecthandle.h"

#include <assert.h>


std::shared_ptr<WorldObjectHandle> WorldObjectHandle::s_nullInstance;

WorldObjectHandle::WorldObjectHandle(WorldObject* worldObject) :
    m_worldObject(worldObject)
{
}

WorldObject* WorldObjectHandle::get() {
    return m_worldObject;
}

bool WorldObjectHandle::valid() const {
    return m_worldObject != nullptr;
}

void WorldObjectHandle::invalidate() {
    m_worldObject = nullptr;
}

std::shared_ptr<WorldObjectHandle> WorldObjectHandle::nullHandle() {
    if (s_nullInstance == nullptr) {
        s_nullInstance = std::make_shared<WorldObjectHandle>(nullptr);
    }
    return s_nullInstance;
}


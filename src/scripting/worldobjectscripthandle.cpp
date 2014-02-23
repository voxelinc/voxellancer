#include "worldobjectscripthandle.h"


WorldObjectScriptHandle::WorldObjectScriptHandle(int key, WorldObject* worldObject):
    m_key(key),
    m_worldObject(worldObject)
{

}

bool WorldObjectScriptHandle::valid() const {
    return m_worldObject.valid();
}

int WorldObjectScriptHandle::key() const {
    return m_key;
}

WorldObject* WorldObjectScriptHandle::worldObject() {
    return m_worldObject.get();
}

#pragma once

#include "worldobject/worldobject.h"


class WorldObject;

/*
    Currently pretty much same as Handle<WorldObject>, but will store event specially filtered
    for scripts in the future
*/
class WorldObjectScriptHandle {
public:
    WorldObjectScriptHandle(int key, WorldObject* worldObject);

    bool valid() const;

    int key() const;

    WorldObject* worldObject();


protected:
    int m_key;
    Handle<WorldObject> m_worldObject;
};


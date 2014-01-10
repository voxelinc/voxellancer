#pragma once

#include <memory>

#include "worldobject.h"

/*
 contains a pointer to a worldobject
 use this handle if it is possible that
 the worldobject gets deleted. check if
 the handle is still valid if you access it
*/
class WorldObjectHandle {
    // only the WorldObject destructor should invalidate handles
    friend WorldObject::~WorldObject();

public:
    WorldObjectHandle(WorldObject* worldObject);

    // returns WorldObject* or nullptr
    WorldObject* get();

    bool valid() const;

    static std::shared_ptr<WorldObjectHandle> nullHandle();


protected:
    void invalidate();

    static std::shared_ptr<WorldObjectHandle> s_nullInstance;
    WorldObject* m_worldObject;
};

#pragma once

#include <cinttypes>

#include "collisionfilterclass.h"

class WorldObject;

class CollisionFilter {
public:
    CollisionFilter(WorldObject* owner, CollisionFilterClass collisionFilterClass, uint32_t collisionMask = 0xFFFFFFFF);

    CollisionFilterClass collisionFilterClass() const;
    uint32_t collisionMask() const;

    void setCollideableWith(CollisionFilterClass collisionFilterClass, bool collides);
    bool isCollideableWith(const CollisionFilter* other) const;
        
    virtual WorldObject* owner() const;
    virtual WorldObject* creator() const;

protected:
    CollisionFilterClass m_collisionFilterClass;
    uint32_t m_collisionMask;
    WorldObject* m_owner;

    bool areMasksCollidable(const CollisionFilter* other) const;
    virtual bool specialIsCollideableWith(const CollisionFilter* other) const;
};


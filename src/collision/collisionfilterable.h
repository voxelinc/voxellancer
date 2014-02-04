#pragma once

#include <string>
#include <cinttypes>

#include "collisionfilterclass.h"


class CollisionFilterable {
public:
    CollisionFilterable(CollisionFilterClass collisionFilterClass, uint32_t collisionMask = 0xFFFFFFFF);

    CollisionFilterClass collisionFilterClass() const;
    void setCollisionFilterClass(CollisionFilterClass collisionFilterClass);

    uint32_t collisionMask() const;

    void setCollideableWith(CollisionFilterClass collisionFilterClass, bool collides);

    bool isCollideableWith(CollisionFilterClass collisionFilterClass) const;
    bool isCollideableWith(const CollisionFilterable *other) const;

    bool areMasksCollidable(const CollisionFilterable *other) const;
    virtual bool specialIsCollideableWith(const CollisionFilterable *other) const;



protected:
    CollisionFilterClass m_collisionFilterClass;
    uint32_t m_collisionMask;
};


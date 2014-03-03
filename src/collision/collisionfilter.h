#pragma once

#include <cinttypes>


class WorldObject;
enum class WorldObjectType;

class CollisionFilter {
public:
    CollisionFilter(WorldObject* owner, uint32_t collisionMask = 0xFFFFFFFF);

    uint32_t collisionMask() const;

    void setCollideableWith(WorldObjectType objectType, bool collides);
    bool isCollideableWith(const CollisionFilter* other) const;

    virtual WorldObject* owner() const;
    virtual WorldObject* creator() const;


protected:
    uint32_t m_collisionMask;
    WorldObject* m_owner;

    bool areMasksCollidable(const CollisionFilter* other) const;
    virtual bool specialIsCollideableWith(const CollisionFilter* other) const;
};


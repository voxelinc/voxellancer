#include "collisionfilter.h"

#include "worldobject/worldobject.h"


CollisionFilter::CollisionFilter(WorldObject* owner, uint32_t collisionMask):
    m_owner(owner),
    m_collisionMask(collisionMask)
{
}

uint32_t CollisionFilter::collisionMask() const {
    return m_collisionMask;
}

void CollisionFilter::setCollideableWith(WorldObjectType objectType, bool collides) {
    if(collides) {
        m_collisionMask |= static_cast<uint32_t>(objectType);
    }
    else {
        m_collisionMask &= ~static_cast<uint32_t>(objectType);
    }
}

bool CollisionFilter::isCollideableWith(const CollisionFilter* other) const {
    return  (owner() != other->owner()) && areMasksCollidable(other) && specialIsCollideableWith(other) && other->specialIsCollideableWith(this);
}

bool CollisionFilter::areMasksCollidable(const CollisionFilter* other) const {
    return (static_cast<uint32_t>(m_owner->objectType()) & other->collisionMask()) &&
           (static_cast<uint32_t>(other->owner()->objectType()) & m_collisionMask);
}

bool CollisionFilter::specialIsCollideableWith(const CollisionFilter* other) const {
    return true;
}

WorldObject* CollisionFilter::creator() const {
    return nullptr;
}

WorldObject* CollisionFilter::owner() const {
    return m_owner;
}


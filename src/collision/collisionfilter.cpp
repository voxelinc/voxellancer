#include "collisionfilter.h"

#include <iostream>


CollisionFilter::CollisionFilter(WorldObject* owner, CollisionFilterClass collisionFilterClass, uint32_t collisionMask):
    m_owner(owner),
    m_collisionFilterClass(collisionFilterClass),
    m_collisionMask(collisionMask)
{
}

CollisionFilterClass CollisionFilter::collisionFilterClass() const {
    return m_collisionFilterClass;
}

uint32_t CollisionFilter::collisionMask() const {
    return m_collisionMask;
}

void CollisionFilter::setCollideableWith(CollisionFilterClass collisionFilterClass, bool collides) {
    if(collides) {
        m_collisionMask |= static_cast<uint32_t>(collisionFilterClass);
    }
    else {
        m_collisionMask &= ~static_cast<uint32_t>(collisionFilterClass);
    }
}

bool CollisionFilter::isCollideableWith(const CollisionFilter* other) const {
    return  (owner() != other->owner()) && areMasksCollidable(other) && specialIsCollideableWith(other) && other->specialIsCollideableWith(this);
}

bool CollisionFilter::areMasksCollidable(const CollisionFilter* other) const {
    return (static_cast<uint32_t>(m_collisionFilterClass) & other->collisionMask()) &&
           (static_cast<uint32_t>(other->collisionFilterClass()) & m_collisionMask);
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


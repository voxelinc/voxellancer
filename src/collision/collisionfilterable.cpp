#include "collisionfilterable.h"

#include <iostream>


CollisionFilterable::CollisionFilterable(CollisionFilterClass collisionFilterClass, uint32_t collisionMask):
    m_collisionFilterClass(collisionFilterClass),
    m_collisionMask(collisionMask)
{
}

CollisionFilterClass CollisionFilterable::collisionFilterClass() const {
    return m_collisionFilterClass;
}

uint32_t CollisionFilterable::collisionMask() const {
    return m_collisionMask;
}

void CollisionFilterable::setCollideableWith(CollisionFilterClass collisionFilterClass, bool collides) {
    if(collides) {
        m_collisionMask |= static_cast<uint32_t>(collisionFilterClass);
    }
    else {
        m_collisionMask &= ~static_cast<uint32_t>(collisionFilterClass);
    }
}

bool CollisionFilterable::isCollideableWith(const CollisionFilterable *other) const {
    return  (this != other) && areMasksCollidable(other) && specialIsCollideableWith(other) && other->specialIsCollideableWith(this);
}

bool CollisionFilterable::areMasksCollidable(const CollisionFilterable *other) const {
    return (static_cast<uint32_t>(m_collisionFilterClass) & other->collisionMask()) &&
           (static_cast<uint32_t>(other->collisionFilterClass()) & m_collisionMask);
}

bool CollisionFilterable::specialIsCollideableWith(const CollisionFilterable *other) const {
    return true;
}


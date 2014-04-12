#include "collisionfilterignoringcreator.h"


CollisionFilterIgnoringCreator::CollisionFilterIgnoringCreator(WorldObject* owner, WorldObject* creator, uint32_t collisionMask):
    CollisionFilter(owner, collisionMask),
    m_creator(creator)
{

}

bool CollisionFilterIgnoringCreator::specialIsCollideableWith(const CollisionFilter *other) const {
    // prevent shooting down or colliding with your own rockets/bullets
    return m_creator && (m_creator != other->owner() && m_creator != other->creator());
}

WorldObject* CollisionFilterIgnoringCreator::creator() const {
    return m_creator;
}


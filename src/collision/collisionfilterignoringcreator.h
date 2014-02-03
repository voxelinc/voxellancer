#pragma once

#include "collisionfilter.h"

class CollisionFilterIgnoringCreator : public CollisionFilter {
public:
    CollisionFilterIgnoringCreator(WorldObject* owner, WorldObject* creator, CollisionFilterClass collisionFilterClass, uint32_t collisionMask = 0xFFFFFFFF);

    virtual WorldObject* creator() const override;

protected:
    WorldObject* m_creator;
  
    virtual bool specialIsCollideableWith(const CollisionFilter *other) const override;
};
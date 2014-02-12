#include "split.h"
#include "collision/collisionfilterclass.h"
#include "collision/collisionfilter.h"


Split::Split(const Transform& transform)
{
    setTransform(transform);
    setCollisionFilter(new CollisionFilter(this, CollisionFilterClass::Other));
}


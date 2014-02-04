#include "split.h"
#include "collision/collisionfilterclass.h"
#include "collision/collisionfilter.h"


Split::Split(const Transform& transform):
    WorldObject(new CollisionFilter(this, CollisionFilterClass::Other), transform.scale())
{
    m_transform.setPosition(transform.position());
    m_transform.setOrientation(transform.orientation());
    m_transform.setCenter(transform.center());
}


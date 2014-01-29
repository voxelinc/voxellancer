#include "split.h"

Split::Split(const Transform& transform, CollisionFilterClass collisionFilterClass):
    WorldObject(collisionFilterClass, transform.scale())
{
    m_transform.setPosition(transform.position());
    m_transform.setOrientation(transform.orientation());
    m_transform.setCenter(transform.center());
}


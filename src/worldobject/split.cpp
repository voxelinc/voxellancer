#include "split.h"

Split::Split(const Transform& transform, CollisionFilterClass collisionFilterClass):
    WorldObject(transform.scale(), collisionFilterClass)
{
    m_transform.setPosition(transform.position());
    m_transform.setOrientation(transform.orientation());
    m_transform.setCenter(transform.center());
}

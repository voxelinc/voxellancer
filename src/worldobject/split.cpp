#include "split.h"

Split::Split(const WorldTransform& transform, CollisionFilterClass collisionFilterClass):
    WorldObject(transform.scale(), glm::vec3(0), collisionFilterClass)
{
    m_transform.setPosition(transform.position());
    m_transform.setOrientation(transform.orientation());
    m_transform.setCenter(transform.center());
}

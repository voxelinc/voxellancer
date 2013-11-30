#include "worldobject.h"


CollisionDetector * WorldObject::collisionDetector()
{
    return &m_collisionDetector;
}

void WorldObject::updateGeode()
{
    m_collisionDetector.geode()->setAABB(aabb());
}


AABB WorldObject::aabb() {
    return aabb(m_physics.transform());
}

Sphere WorldObject::sphere() {
    return sphere(m_physics.transform());
}

void WorldObject::update(float delta_sec)
{

}

void WorldObject::move(float delta_sec)
{
    m_physics.move(delta_sec);
}

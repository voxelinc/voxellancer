#include "collision.h"

#include "world/worldobject.h"
#include "voxel/voxel.h"



CollisionParticipant::CollisionParticipant(WorldObject *worldObject, Voxel *voxel, const glm::vec3 &speed):
    m_worldObject(worldObject),
    m_voxel(voxel),
    m_speed(speed)
{

}

WorldObject *CollisionParticipant::worldObject() {
    return m_worldObject;
}

Voxel *CollisionParticipant::voxel() {
    return m_voxel;
}

glm::vec3 CollisionParticipant::speed() const {
    return m_speed;
}

Collision::Collision(const CollisionParticipant &a, const CollisionParticipant &b):
    m_a(a),
    m_b(b)
{

}

const CollisionParticipant &Collision::a() const {
    return m_a;
}

const CollisionParticipant &Collision::b() const {
    return m_b;
}


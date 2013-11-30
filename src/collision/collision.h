#pragma once

#include <glm/glm.hpp>


class WorldObject;
class Voxel;

class CollisionParticipant
{
public:
    CollisionParticipant(WorldObject *worldObject, Voxel *voxel, const glm::vec3 &speed);

    WorldObject *worldObject();
    Voxel *voxel();
    glm::vec3 speed() const;


protected:
    WorldObject *m_worldObject;
    Voxel *m_voxel;
    glm::vec3 m_speed;
};

class Collision
{
public:
    Collision(const CollisionParticipant &a, const CollisionParticipant &b);

    const CollisionParticipant &a() const;
    const CollisionParticipant &b() const;

protected:
    CollisionParticipant m_a, m_b;
};


#pragma once

#include <glm/glm.hpp>


class WorldObject;
class Voxel;

class VoxelCollisionParticipant
{
public:
    VoxelCollisionParticipant(WorldObject* worldObject, Voxel* voxel, const glm::vec3& speed);

    WorldObject* worldObject();
    Voxel* voxel();
    const glm::vec3& speed() const;


protected:
    WorldObject* m_worldObject;
    Voxel* m_voxel;
    glm::vec3 m_speed;
};

class VoxelCollision
{
public:
    VoxelCollision(const VoxelCollisionParticipant& a, const VoxelCollisionParticipant& b);

    VoxelCollisionParticipant& a();
    VoxelCollisionParticipant& b();

protected:
    VoxelCollisionParticipant m_a, m_b;
};


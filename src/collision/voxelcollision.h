#pragma once

#include <glm/glm.hpp>


class WorldObject;
class Voxel;

class VoxelCollisionParticipant
{
public:
    VoxelCollisionParticipant(WorldObject* worldObject, Voxel* voxel);

    WorldObject* worldObject();
    Voxel* voxel();

protected:
    WorldObject* m_worldObject;
    Voxel* m_voxel;
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


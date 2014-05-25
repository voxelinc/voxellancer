#pragma once

#include <glm/glm.hpp>

#include <glow/ref_ptr.h>


class WorldObject;
class Voxel;

class VoxelCollisionParticipant {
public:
    VoxelCollisionParticipant(WorldObject* worldObject, Voxel* voxel);

    WorldObject* worldObject();
    Voxel* voxel();


protected:
    glow::ref_ptr<WorldObject> m_worldObject;
    Voxel* m_voxel;
};

class VoxelCollision {
public:
    VoxelCollision(const VoxelCollisionParticipant& a, const VoxelCollisionParticipant& b);

    VoxelCollisionParticipant& a();
    VoxelCollisionParticipant& b();


protected:
    VoxelCollisionParticipant m_a, m_b;
};


#include "voxelcollision.h"

#include "worldobject/worldobject.h"
#include "voxel/voxel.h"


VoxelCollisionParticipant::VoxelCollisionParticipant(WorldObject* worldObject, Voxel* voxel):
    m_worldObject(worldObject),
    m_voxel(voxel)
{

}

WorldObject* VoxelCollisionParticipant::worldObject() {
    return m_worldObject;
}

Voxel* VoxelCollisionParticipant::voxel() {
    return m_voxel;
}

VoxelCollision::VoxelCollision(const VoxelCollisionParticipant& a, const VoxelCollisionParticipant& b):
    m_a(a),
    m_b(b)
{

}

VoxelCollisionParticipant& VoxelCollision::a() {
    return m_a;
}

VoxelCollisionParticipant& VoxelCollision::b() {
    return m_b;
}


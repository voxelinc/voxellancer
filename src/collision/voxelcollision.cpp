#include "voxelcollision.h"

#include "worldobject/worldobject.h"
#include "voxel/voxel.h"


VoxelCollisionParticipant::VoxelCollisionParticipant(WorldObject* worldObject, Voxel* voxel, const glm::vec3& speed):
    m_worldObject(worldObject),
    m_voxel(voxel),
    m_speed(speed)
{

}

WorldObject* VoxelCollisionParticipant::worldObject() {
    return m_worldObject;
}

Voxel* VoxelCollisionParticipant::voxel() {
    return m_voxel;
}

const glm::vec3 &VoxelCollisionParticipant::speed() const {
    return m_speed;
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


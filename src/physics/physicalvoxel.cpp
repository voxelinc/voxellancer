#include "physicalvoxel.h"


PhysicalVoxel::PhysicalVoxel(PhysicalVoxelCluster *physicalVoxelCluster):
    m_physicalVoxelCluster(physicalVoxelCluster),
    m_hp(0.0f),
    m_mass(0.0f)
{

}

PhysicalVoxelCluster *PhysicalVoxel::physicalVoxelCluster() {
    return m_physicalVoxelCluster;
}

const PhysicalVoxelCluster *PhysicalVoxel::physicalVoxelCluster() const {
    return m_physicalVoxelCluster;
}

float PhysicalVoxel::hp() const {
    return m_hp;
}

void PhysicalVoxel::setHp(float hp) {
    m_hp = hp;
}

float PhysicalVoxel::mass() const {
    return m_mass;
}

void PhysicalVoxel::setMass(float mass) {
    m_mass = mass;
}

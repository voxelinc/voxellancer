#include "worldobject.h"


WorldObject::WorldObject(float scale):
    m_transform(glm::vec3(0), scale),
    m_voxelCluster(),
    m_physics(*this),
    m_collisionDetector(*this)
{

}

WorldObject::~WorldObject() {

}

CollisionDetector* WorldObject::collisionDetector(){
    return &m_collisionDetector;
}

Physics* WorldObject::physics() {
    return &m_physics;
}

VoxelCluster* WorldObject::voxelCluster() {
    return &m_voxelCluster;
}

AABB WorldObject::aabb() {
    return m_voxelCluster.aabb(m_transform);
}

Sphere WorldObject::sphere() {
    return m_voxelCluster.sphere(m_transform);
}

void WorldObject::update(float delta_sec) {

}

std::list<Impact>& WorldObject::move(float delta_sec) {
    return m_physics.move(delta_sec);
}

void WorldObject::addVoxel(Voxel * voxel) {
    m_voxelCluster.addVoxel(voxel);
    m_physics.addVoxel(voxel);
    m_collisionDetector.addVoxel(voxel);
}

void WorldObject::removeVoxel(const glm::ivec3 & position) {
    m_voxelCluster.removeVoxel(position);
    m_physics.removeVoxel(position);
    m_collisionDetector.removeVoxel(position);
}

WorldTransform& WorldObject::transform() {
    return m_transform;
}

void WorldObject::finishInitialization() {
    m_physics.finishInitialization();
    m_collisionDetector.finishInitialization();
}

Voxel *WorldObject::crucialVoxel() {
    return nullptr;
}

void WorldObject::accelerate(glm::vec3 direction) {
    m_physics.accelerate(direction);
}

void WorldObject::accelerateAngular(glm::vec3 axis) {
    m_physics.accelerateAngular(axis);
}

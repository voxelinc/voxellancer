#include "worldobject.h"

#include "utils/tostring.h"


WorldObject::WorldObject(float scale):
    VoxelCluster(scale),
    m_physics(*this),
    m_collisionDetector(*this),
    m_hudInfo()
{

}

WorldObject::~WorldObject() {

}

CollisionDetector& WorldObject::collisionDetector(){
    return m_collisionDetector;
}

Physics& WorldObject::physics() {
    return m_physics;
}

HUDInfo& WorldObject::hudInfo(){
    return m_hudInfo;
}

AABB WorldObject::aabb() {
    return m_collisionDetector.aabb(m_transform);
}

Sphere WorldObject::sphere() {
    return m_collisionDetector.sphere(m_transform);
}

void WorldObject::update(float delta_sec) {

}

std::list<Impact>& WorldObject::move(float delta_sec) {
    return m_physics.move(delta_sec);
}

void WorldObject::addVoxel(Voxel * voxel) {
    VoxelCluster::addVoxel(voxel);
    m_physics.addVoxel(voxel);
    m_collisionDetector.addVoxel(voxel);
}

void WorldObject::removeVoxel(const glm::ivec3 & position) {
    m_collisionDetector.removeVoxel(position);
    m_physics.removeVoxel(position);
    VoxelCluster::removeVoxel(position);
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

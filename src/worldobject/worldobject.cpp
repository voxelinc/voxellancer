#include "worldobject.h"

#include "utils/tostring.h"


WorldObject::WorldObject(float scale) :
    WorldObject(new Physics(*this), new CollisionDetector(*this), scale)
{
}

WorldObject::WorldObject(Physics* physics, CollisionDetector* detector, float scale) :
    VoxelCluster(scale),
    m_physics(physics),
    m_collisionDetector(detector),
    m_hudInfo(),
    m_crucialVoxel(nullptr)
{
}

WorldObject::WorldObject(const WorldTransform& transform):
    WorldObject(transform.scale())
{
    m_transform.setPosition(transform.position());
    m_transform.setOrientation(transform.orientation());
    m_transform.setCenter(transform.center());
}

WorldObject::~WorldObject() {

}

CollisionDetector& WorldObject::collisionDetector(){
    return *m_collisionDetector;
}

Physics& WorldObject::physics() {
    return *m_physics;
}

HUDInfo& WorldObject::hudInfo(){
    return m_hudInfo;
}

AABB WorldObject::aabb() {
    return m_collisionDetector->aabb(m_transform);
}

Sphere WorldObject::sphere() {
    return m_collisionDetector->sphere(m_transform);
}

void WorldObject::update(float delta_sec) {

}

std::list<Impact>& WorldObject::updatePosition(float delta_sec) {
    return m_physics->move(delta_sec);
}

void WorldObject::addVoxel(Voxel * voxel) {
    VoxelCluster::addVoxel(voxel);
    m_physics->addVoxel(voxel);
    m_collisionDetector->addVoxel(voxel);
}

void WorldObject::removeVoxel(const glm::ivec3 & position) {
    m_collisionDetector->removeVoxel(position);
    m_physics->removeVoxel(position);
    if (m_crucialVoxel != nullptr && position == m_crucialVoxel->gridCell()) {
        // do spectacular stuff like an explosion
        m_crucialVoxel = nullptr;
    }
    VoxelCluster::removeVoxel(position);
}

void WorldObject::finishInitialization() {
    m_transform.setCenter(m_physics->calculateMassAndCenter());
    m_collisionDetector->finishInitialization();
}

void WorldObject::recalculateCenterAndMass() {
    //m_transform.setCenter(m_physics->calculateMassAndCenter()); TODO!!!
    m_collisionDetector->updateGeode();
}




void WorldObject::accelerate(glm::vec3 direction) {
    m_physics->accelerate(direction);
}

void WorldObject::accelerateAngular(glm::vec3 axis) {
    m_physics->accelerateAngular(axis);
}

Voxel *WorldObject::crucialVoxel() {
    return m_crucialVoxel;
}
void WorldObject::setCrucialVoxel(glm::ivec3 pos) {
    m_crucialVoxel = voxel(pos);
}


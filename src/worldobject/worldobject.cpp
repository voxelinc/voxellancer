#include "worldobject.h"

#include <glow/AutoTimer.h>

#include "utils/tostring.h"
#include "voxel/specialvoxels/enginevoxel.h"
#include "voxel/specialvoxels/hardpointvoxel.h"
#include "voxel/specialvoxels/cockpitvoxel.h"
#include "voxel/specialvoxels/fuelvoxel.h"


WorldObject::WorldObject(CollisionFilterClass collisionFilterClass):
    WorldObject(1.0f, glm::vec3(0), collisionFilterClass)
{

}

WorldObject::WorldObject(float scale, glm::vec3 center, CollisionFilterClass collisionFilterClass) :
    WorldObject(new Physics(*this, scale), new CollisionDetector(*this), scale, collisionFilterClass)
{
    m_transform.setCenter(center);
}

WorldObject::WorldObject(Physics* physics, CollisionDetector* detector, float scale, CollisionFilterClass collisionFilterClass) :
    CollisionFilterable(collisionFilterClass),
    VoxelCluster(scale),
    m_physics(physics),
    m_collisionDetector(detector),
    m_objectInfo(),
    m_crucialVoxel(nullptr)
{
}

WorldObject::WorldObject(const WorldTransform& transform, CollisionFilterClass collisionFilterClass):
    WorldObject(transform.scale(), transform.center(), collisionFilterClass)
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

ObjectInfo& WorldObject::objectInfo(){
    return m_objectInfo;
}

void WorldObject::update(float deltaSec) {

}

std::list<VoxelCollision>& WorldObject::performMovement(float deltaSec) {
    return m_physics->move(deltaSec);
}

void WorldObject::addVoxel(Voxel* voxel) {
    VoxelCluster::addVoxel(voxel);

    m_physics->addVoxel(voxel);
    m_collisionDetector->addVoxel(voxel);
    m_collisionDetector->updateGeode();
}

void WorldObject::removeVoxel(Voxel* voxel) {
    assert(voxel != nullptr);

    voxel->onRemoval();

    if (voxel == m_crucialVoxel) {
        m_crucialVoxel = nullptr;  // do spectacular stuff like an explosion
    }

    m_collisionDetector->removeVoxel(voxel);
    m_physics->removeVoxel(voxel);
    VoxelCluster::removeVoxel(voxel);
}

void WorldObject::addEngineVoxel(EngineVoxel* voxel){
    addVoxel(voxel);
}

void WorldObject::addHardpointVoxel(HardpointVoxel* voxel){
    addVoxel(voxel);
}

void WorldObject::addCockpitVoxel(CockpitVoxel* voxel){
    addVoxel(voxel);
}

void WorldObject::addFuelVoxel(FuelVoxel* voxel){
    addVoxel(voxel);
}

void WorldObject::accelerate(const glm::vec3& direction) {
    m_physics->accelerate(direction);
}

void WorldObject::accelerateAngular(const glm::vec3& axis) {
    m_physics->accelerateAngular(axis);
}

void WorldObject::setCenterAndAdjustPosition(const glm::vec3& newCenter) {
    m_transform.setCenterAndAdjustPosition(newCenter);
}

void WorldObject::updateTransformAndGeode(const glm::vec3& position, const glm::quat& orientation) {
    setOrientation(orientation);
    setPosition(position);
    m_collisionDetector->updateGeode();
}

Voxel *WorldObject::crucialVoxel() {
    return m_crucialVoxel;
}

void WorldObject::setCrucialVoxel(const glm::ivec3& cell) {
    m_crucialVoxel = voxel(cell);
}

void WorldObject::onCollision(){

}

void WorldObject::onSpawnFail(){

}

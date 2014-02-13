#include "worldobject.h"

#include "utils/tostring.h"
#include "voxel/specialvoxels/enginevoxel.h"
#include "voxel/specialvoxels/hardpointvoxel.h"
#include "voxel/specialvoxels/cockpitvoxel.h"
#include "voxel/specialvoxels/fuelvoxel.h"
#include "worldobject/handle/handle.h"
#include "collision/collisiondetector.h"
#include "collision/collisionfilter.h"


WorldObject::WorldObject() :
    WorldObject(new CollisionFilter(this,CollisionFilterClass::Other))
{

}

WorldObject::WorldObject(CollisionFilter* collisionFilter, float scale) :
    VoxelCluster(scale),
    m_physics(*this, scale),
    m_collisionDetector(new CollisionDetector(*this)),
    m_objectInfo(),
    m_crucialVoxel(nullptr),
    m_collisionFieldOfDamage(glm::half_pi<float>()),
    m_handle(Handle<WorldObject>(this)),
    m_scheduledForDeletion(false),
    m_collisionFilter(collisionFilter)
{
}

WorldObject::~WorldObject() {
     m_handle.invalidate();
}

CollisionDetector& WorldObject::collisionDetector() {
    return *m_collisionDetector;
}

CollisionFilter& WorldObject::collisionFilter() {
    return *m_collisionFilter;
}

Physics& WorldObject::physics() {
    return m_physics;
}

ObjectInfo& WorldObject::objectInfo() {
    return m_objectInfo;
}

void WorldObject::update(float deltaSec) {

}

std::list<VoxelCollision>& WorldObject::performMovement(float deltaSec) {
    return m_physics.move(deltaSec);
}

void WorldObject::addVoxel(Voxel* voxel) {
    VoxelCluster::addVoxel(voxel);

    m_physics.addVoxel(voxel);
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
    m_physics.removeVoxel(voxel);
    VoxelCluster::removeVoxel(voxel);
}

void WorldObject::addEngineVoxel(EngineVoxel* voxel) {
    addVoxel(voxel);
}

void WorldObject::addHardpointVoxel(HardpointVoxel* voxel) {
    addVoxel(voxel);
}

void WorldObject::addCockpitVoxel(CockpitVoxel* voxel) {
    addVoxel(voxel);
}

void WorldObject::addFuelVoxel(FuelVoxel* voxel) {
    addVoxel(voxel);
}

void WorldObject::accelerate(const glm::vec3& direction) {
    m_physics.accelerate(direction);
}

void WorldObject::accelerateAngular(const glm::vec3& axis) {
    m_physics.accelerateAngular(axis);
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

void WorldObject::onCollision() {

}

void WorldObject::onSpawnFail() {

}

Handle<WorldObject>& WorldObject::handle() {
    return m_handle;
}

bool WorldObject::scheduledForDeletion() {
    return m_scheduledForDeletion;
}

void WorldObject::onScheduleForDeletion() {
    m_scheduledForDeletion = true;
}

float WorldObject::collisionFieldOfDamage() {
    return m_collisionFieldOfDamage;
}

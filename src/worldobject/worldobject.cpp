#include "worldobject.h"

#include "resource/clustercache.h"

#include "utils/tostring.h"

#include "worldobject/handle/handle.h"


WorldObject::WorldObject(CollisionFilterClass collisionFilterClass, float scale):
    CollisionFilterable(collisionFilterClass),
    VoxelCluster(scale),
    m_physics(*this, scale),
    m_collisionDetector(*this),
    m_objectInfo(),
    m_components(this),
    m_crucialVoxel(nullptr),
    m_handle(Handle<WorldObject>(this)),
    m_scheduledForDeletion(false)
{
}

 WorldObject::~WorldObject() {
     m_handle.invalidate();
}

CollisionDetector& WorldObject::collisionDetector() {
    return m_collisionDetector;
}

Physics& WorldObject::physics() {
    return m_physics;
}

ObjectInfo& WorldObject::objectInfo() {
    return m_objectInfo;
}

WorldObjectComponents& WorldObject::components() {
    return m_components;
}

void WorldObject::load(const std::string& key) {
    std::string clusterFile = Property<std::string>(key + ".general.voxelcluster");
    ClusterCache::instance()->fillObject(this, std::string("data/voxelcluster/") + clusterFile);

    m_components.load(key);
}

void WorldObject::update(float deltaSec) {
    Acceleration localAcceleration = m_components.currentAcceleration();

    Acceleration globalAcceleration(
        m_transform.orientation() * localAcceleration.directional(),
        m_transform.orientation() * localAcceleration.angular()
    );

    m_physics.setAcceleration(globalAcceleration);
}

void WorldObject::addVoxel(Voxel* voxel) {
    assert(voxel);

    VoxelCluster::addVoxel(voxel);

    m_physics.addVoxel(voxel);

    m_collisionDetector.addVoxel(voxel);
    m_collisionDetector.updateGeode();
}

void WorldObject::removeVoxel(Voxel* voxel) {
    assert(voxel);

    voxel->onRemoval();

    if (voxel == m_crucialVoxel) {
        m_crucialVoxel = nullptr;  // do spectacular stuff like an explosion
    }

    m_collisionDetector.removeVoxel(voxel);
    m_physics.removeVoxel(voxel);

    VoxelCluster::removeVoxel(voxel);
}

void WorldObject::updateTransformAndGeode(const glm::vec3& position, const glm::quat& orientation) {
    transform().setOrientation(orientation);
    transform().setPosition(position);

    m_collisionDetector.updateGeode();
}

Voxel* WorldObject::crucialVoxel() {
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


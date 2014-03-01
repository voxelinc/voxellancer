#include "worldobject.h"

#include "collision/collisiondetector.h"
#include "collision/collisionfilter.h"

#include "resource/clustercache.h"

#include "utils/tostring.h"

#include "worldobject/handle/handle.h"
#include "physics/physics.h"
#include "ui/objectinfo.h"
#include "voxel/voxel.h"
#include "worldobjectcomponents.h"


WorldObject::WorldObject():
    WorldObject(new CollisionFilter(this), 1.0f)
{

}

WorldObject::WorldObject(CollisionFilter* collisionFilter, float scale):
    VoxelCluster(scale),
    m_physics(new Physics(*this, scale)),
    m_collisionDetector(new CollisionDetector(*this)),
    m_objectInfo(new ObjectInfo()),
    m_components(new WorldObjectComponents(this)),
    m_crucialVoxel(nullptr),
    m_collisionFieldOfDamage(glm::half_pi<float>()),
    m_handle(Handle<WorldObject>(this)),
    m_spawnState(SpawnState::None),
    m_collisionFilter(collisionFilter)
{
}

WorldObject::~WorldObject() {
     m_handle.invalidate();
}

WorldObjectType WorldObject::objectType() const {
    return WorldObjectType::WorldObject;
}

SpawnState WorldObject::spawnState() const {
    return m_spawnState;
}

void WorldObject::setSpawnState(SpawnState spawnState) {
    m_spawnState = spawnState;
}

CollisionDetector& WorldObject::collisionDetector() {
    return *m_collisionDetector;
}

CollisionFilter& WorldObject::collisionFilter() {
    return *m_collisionFilter;
}

void WorldObject::setCollisionFilter(CollisionFilter* collisionFilter) {
    m_collisionFilter.reset(collisionFilter);
}

Physics& WorldObject::physics() {
    return *m_physics;
}

ObjectInfo& WorldObject::objectInfo() {
    return *m_objectInfo;
}

WorldObjectComponents& WorldObject::components() {
    return *m_components;
}

void WorldObject::update(float deltaSec) {
    m_components->update(deltaSec);

    Acceleration localAcceleration = m_components->currentAcceleration();

    Acceleration globalAcceleration(
        m_transform.orientation() * localAcceleration.directional(),
        m_transform.orientation() * localAcceleration.angular()
    );

    m_physics->setAcceleration(globalAcceleration);
}

void WorldObject::addVoxel(Voxel* voxel) {
    assert(voxel);

    VoxelCluster::addVoxel(voxel);

    m_physics->addVoxel(voxel);

    m_collisionDetector->addVoxel(voxel);
    m_collisionDetector->updateGeode();
}

void WorldObject::removeVoxel(Voxel* voxel) {
    assert(voxel);

    voxel->onRemoval();

    if (voxel == m_crucialVoxel) {
        m_crucialVoxel = nullptr;  // do spectacular stuff like an explosion
    }

    m_collisionDetector->removeVoxel(voxel);
    m_physics->removeVoxel(voxel);

    VoxelCluster::removeVoxel(voxel);
}

void WorldObject::updateTransformAndGeode(const glm::vec3& position, const glm::quat& orientation) {
    transform().setOrientation(orientation);
    transform().setPosition(position);

    m_collisionDetector->updateGeode();
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

float WorldObject::collisionFieldOfDamage() const {
    return m_collisionFieldOfDamage;
}

void WorldObject::setCollisionFieldOfDamage(float collisionFieldOfDamage) {
    m_collisionFieldOfDamage = collisionFieldOfDamage;
}


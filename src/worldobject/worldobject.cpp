#include "worldobject.h"

#include "collision/collisiondetector.h"
#include "collision/collisionfilter.h"

#include "resource/clustercache.h"

#include "utils/tostring.h"

#include "physics/physics.h"
#include "worldobject/worldobjectinfo.h"
#include "voxel/voxel.h"
#include "worldobjectcomponents.h"


WorldObject::WorldObject() :
    VoxelCluster(1.0f),
    m_physics(new Physics(*this)),
    m_collisionDetector(new CollisionDetector(*this)),
    m_info(new WorldObjectInfo()),
    m_components(new WorldObjectComponents(this)),
    m_crucialVoxel(nullptr),
    m_collisionFieldOfDamage(glm::half_pi<float>()),
    m_spawnState(SpawnState::None),
    m_collisionFilter(new CollisionFilter(this)),
    m_crucialVoxelDestroyed(false),
    m_cockpitVoxelsDestroyed(false)
{
}

WorldObject::WorldObject(const Transform& transform) :
    WorldObject()
{
    setTransform(transform);
}

WorldObject::~WorldObject() = default;

WorldObjectType WorldObject::objectType() const {
    return WorldObjectType::Other;
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

const Physics& WorldObject::physics() const {
    return *m_physics;
}

WorldObjectInfo& WorldObject::info() {
    return *m_info;
}

WorldObjectComponents& WorldObject::components() {
    return *m_components;
}

const WorldObjectComponents& WorldObject::components() const {
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
        m_crucialVoxelDestroyed = true;
        m_crucialVoxel = nullptr;
    }

    if (m_cockpitVoxels.erase(voxel->gridCell())) {
        m_cockpitVoxelsDestroyed = m_cockpitVoxels.empty();
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
    assert(m_crucialVoxel == nullptr);

    m_crucialVoxel = voxel(cell);
    m_crucialVoxelDestroyed = false;
}

bool WorldObject::isCrucialVoxelDestroyed(){
    return m_crucialVoxelDestroyed;
}

void WorldObject::onCollision() {

}

void WorldObject::onSpawnFail() {

}

float WorldObject::collisionFieldOfDamage() const {
    return m_collisionFieldOfDamage;
}

void WorldObject::setCollisionFieldOfDamage(float collisionFieldOfDamage) {
    m_collisionFieldOfDamage = collisionFieldOfDamage;
}

bool WorldObject::passiveForCollisionDetection() {
    return false;
}

std::unordered_map<glm::ivec3, Voxel*> WorldObject::cockpitVoxels() {
    return m_cockpitVoxels;
}

void WorldObject::addCockpitVoxel(const glm::ivec3& cell) {
    m_cockpitVoxels[cell] = voxel(cell);
    m_cockpitVoxelsDestroyed = false;
}

bool WorldObject::areCockpitVoxelsDestroyed() {
    return m_cockpitVoxelsDestroyed;
}


#include "worldobject.h"

#include "utils/tostring.h"
#include "voxel/specialvoxels/enginevoxel.h"
#include "voxel/specialvoxels/hardpointvoxel.h"
#include "voxel/specialvoxels/cockpitvoxel.h"
#include "voxel/specialvoxels/fuelvoxel.h"


WorldObject::WorldObject(float scale, glm::vec3 center) :
    WorldObject(new Physics(*this), new CollisionDetector(*this), scale)
{
    m_transform.setCenter(center);
}

WorldObject::WorldObject(Physics* physics, CollisionDetector* detector, float scale) :
    VoxelCluster(scale),
    m_physics(physics),
    m_collisionDetector(detector),
    m_objectInfo(),
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

ObjectInfo& WorldObject::objectInfo(){
    return m_objectInfo;
}

AABB WorldObject::aabb() {
    return m_collisionDetector->aabb(m_transform);
}

Sphere WorldObject::sphere() {
    return m_collisionDetector->sphere(m_transform);
}

void WorldObject::update(float delta_sec) {

}

std::list<VoxelCollision>& WorldObject::performMovement(float delta_sec) {
    return m_physics->move(delta_sec);
}

void WorldObject::addVoxel(Voxel* voxel) {
    VoxelCluster::addVoxel(voxel);
    m_physics->addVoxel(voxel);
    m_collisionDetector->addVoxel(voxel);
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

void WorldObject::removeVoxel(const glm::ivec3& position) {
    Voxel* voxel = m_voxels[position];
    assert(voxel != nullptr);
    voxel->onRemoval();
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
    m_physics->calculateMassAndCenter();
    m_collisionDetector->updateGeode();
}

void WorldObject::accelerate(const glm::vec3& direction) {
    m_physics->accelerate(direction);
}

void WorldObject::accelerateAngular(const glm::vec3& axis) {
    m_physics->accelerateAngular(axis);
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

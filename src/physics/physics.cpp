#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include "physics.h"

#include "worldtransform.h"
#include "collision/collisiondetector.h"
#include "worldobject/worldobject.h"
#include "worldtree/worldtreegeode.h"
#include "world/world.h"
#include "worldtree/worldtree.h"


Physics::Physics(WorldObject& worldObject) :
    m_speed(0),
    m_angularSpeed(0),
    m_acceleration(0),
    m_angularAcceleration(0),
    m_dampening("physics.globalDampening"),
    m_angularDampening("physics.globalAngularDampening"),
    m_mass(0),
    m_massValid(true),
    m_worldObject(worldObject)
{

}

// only neccessary for manually constructed voxelclusters, not if
// the cluster is build from clusterstore
void Physics::finishInitialization() {
    calculateMassAndCenter();
}

Physics::~Physics() {
}

const glm::vec3& Physics::speed() const {
    return m_speed;
}

void Physics::setSpeed(const glm::vec3& speed) {
    m_speed = speed;
}

const glm::vec3& Physics::angularSpeed() const {
    return m_angularSpeed;
}

void Physics::setAngularSpeed(const glm::vec3& angularSpeed) {
    m_angularSpeed = angularSpeed;
}

const glm::vec3& Physics::acceleration() const {
    return m_acceleration;
}

const glm::vec3& Physics::angularAcceleration() const {
    return m_angularAcceleration;
}

float Physics::mass() const {
    return m_mass;
}

bool Physics::massValid() const {
    return m_massValid;
}

void Physics::calculateMassAndCenter() {
    glm::vec3 center;

    if (m_massValid) {
        return;
    }

    m_mass = 0;
    for (auto pair : m_worldObject.voxelMap()) {
        Voxel *voxel = pair.second;
        m_mass += 1.0; // voxel.mass?
        center += glm::vec3(voxel->gridCell()) * 1.0f; // voxel.mass?
    }

    center /= m_mass;
    m_worldObject.transform().setCenter(center);
    m_massValid = true;
}

std::list<VoxelCollision> &Physics::move(float deltaSec) {
    updateSpeed(deltaSec);

    WorldTransform targetTransform(m_worldObject.transform());
    targetTransform.moveWorld(m_speed * deltaSec);
    targetTransform.rotate(glm::quat(m_angularSpeed * deltaSec));

    Movement movement(m_worldObject, m_worldObject.transform(), targetTransform);
    movement.perform();

    return m_worldObject.collisionDetector().lastCollisions();
}

// accelerate along local axis
void Physics::accelerate(const glm::vec3& direction) {
    m_acceleration += m_worldObject.transform().orientation() * direction;
}

// angular acceleration around local axis
void Physics::accelerateAngular(const glm::vec3& axis) {
    m_angularAcceleration += axis;
}

void Physics::addVoxel(Voxel* voxel) {
    m_massValid = false;
}

void Physics::removeVoxel(const glm::ivec3& position) {
    m_massValid = false;
    calculateMassAndCenter();
    //m_worldObject.transform().setPosition(-oldCenter + m_worldObject.transform().center());
    // it would be better to calculate incremental mass/center changes here
    // something like mass -= 1; center -= 1/mass * pos; center /= (mass-1)/mass; should work
    // but there should be tests to verify this! (1 = mass of voxel)
}

void Physics::updateSpeed(float deltaSec){
    m_speed *= (1.f - m_dampening * deltaSec);
    m_speed += m_acceleration * deltaSec;

    m_angularSpeed *= (1.f - m_angularDampening * deltaSec);
    m_angularSpeed = m_angularSpeed + (m_angularAcceleration*deltaSec);

    m_acceleration = glm::vec3(0);
    m_angularAcceleration = glm::vec3(0);
}





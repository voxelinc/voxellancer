#include "physics.h"

#include <functional>
#include <iostream>

#include <glm/gtx/quaternion.hpp>

#include "geometry/transform.h"

#include "collision/collisiondetector.h"

#include "worldobject/worldobject.h"
#include "worldtree/worldtree.h"

#include "worldtree/worldtreegeode.h"

#include "world/world.h"

#include "utils/tostring.h"


Physics::Physics(WorldObject& worldObject, float scale) :
    m_speed(0),
    m_angularSpeed(0),
    m_acceleration(0),
    m_angularAcceleration(0),
    m_dampening(Property<float>("physics.globalDampening")),
    m_angularDampening(Property<float>("physics.globalAngularDampening")),
    m_mass(0),
    m_accumulatedMassVec(0.0f, 0.0f, 0.0f),
    m_worldObject(worldObject)
{
    m_massScaleFactor = glm::pow(scale, 3.f);
}

Physics::~Physics() {
}

float Physics::dampening() {
    return m_dampening;
}

void Physics::setDampening(float dampening) {
    m_dampening = dampening;
}

float Physics::angularDampening() {
    return m_angularDampening;
}

void Physics::setAngularDampening(float angularDampening) {
    m_angularDampening = angularDampening;
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

std::list<VoxelCollision> &Physics::move(float deltaSec) {
    updateSpeed(deltaSec);

    if (m_speed != glm::vec3(0.0f) || m_angularSpeed != glm::vec3(0.0f)) {
        Transform targetTransform(m_worldObject.transform());
        targetTransform.moveWorld(m_speed * deltaSec);
        targetTransform.rotate(glm::quat(m_angularSpeed * deltaSec));

        Movement movement(m_worldObject, m_worldObject.transform(), targetTransform);
        movement.perform();
    }

    return m_worldObject.collisionDetector().lastCollisions();
}

void Physics::accelerate(const glm::vec3& direction) {
    m_acceleration += m_worldObject.transform().orientation() * direction;
}

void Physics::accelerateAngular(const glm::vec3& axis) {
    m_angularAcceleration += axis;
}

void Physics::addVoxel(Voxel* voxel) {
    alterCell(voxel, true);
}

void Physics::removeVoxel(Voxel* voxel) {
    alterCell(voxel, false);
}

void Physics::updateSpeed(float deltaSec) {
    m_speed *= (1.f - m_dampening * deltaSec);
    m_speed += m_acceleration * deltaSec;

    m_angularSpeed *= (1.f - m_angularDampening * deltaSec);
    m_angularSpeed = m_angularSpeed + (m_angularAcceleration*deltaSec);

    m_acceleration = glm::vec3(0);
    m_angularAcceleration = glm::vec3(0);
}

void Physics::alterCell(Voxel* voxel, bool isAdd) {
    float scaledVoxelMass = voxel->normalizedMass() * m_massScaleFactor;
    if (!isAdd) {
        scaledVoxelMass *= -1;
    }

    m_mass = m_mass + scaledVoxelMass;
    m_accumulatedMassVec = m_accumulatedMassVec + glm::vec3(voxel->gridCell()) * scaledVoxelMass;

    if (m_mass > 0.0f) {
        m_worldObject.setCenterAndAdjustPosition(m_accumulatedMassVec / m_mass);
    }  else {
        m_worldObject.setCenterAndAdjustPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    }
}


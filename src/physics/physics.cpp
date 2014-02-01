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
#include "voxel/voxel.h"


Physics::Physics(WorldObject& worldObject, float scale) :
    m_directionalSpeed(0),
    m_angularSpeed(0),
    m_directionalAcceleration(0),
    m_angularAcceleration(0),
    m_directionalDampening(Property<float>("physics.globalDirectionalDampening")),
    m_angularDampening(Property<float>("physics.globalAngularDampening")),
    m_mass(0),
    m_accumulatedMassVec(0.0f, 0.0f, 0.0f),
    m_worldObject(worldObject)
{
    m_massScaleFactor = glm::pow(scale, 3.f);
}

Physics::~Physics() {
}

float Physics::directionalDampening() {
    return m_directionalDampening;
}

void Physics::setDirectionalDampening(float directionalDampening) {
    m_directionalDampening = directionalDampening;
}

float Physics::angularDampening() {
    return m_angularDampening;
}

void Physics::setAngularDampening(float angularDampening) {
    m_angularDampening = angularDampening;
}

const glm::vec3& Physics::directionalSpeed() const {
    return m_directionalSpeed;
}

void Physics::setDirectionalSpeed(const glm::vec3& directionalSpeed) {
    m_directionalSpeed = directionalSpeed;
}

const glm::vec3& Physics::angularSpeed() const {
    return m_angularSpeed;
}

void Physics::setAngularSpeed(const glm::vec3& angularSpeed) {
    m_angularSpeed = angularSpeed;
}

const glm::vec3& Physics::directionalAcceleration() const {
    return m_directionalAcceleration;
}

const glm::vec3& Physics::angularAcceleration() const {
    return m_angularAcceleration;
}

float Physics::mass() const {
    return m_mass;
}

const Transform Physics::projectedTransformIn(float deltaSec){
    Transform targetTransform(m_worldObject.transform());
    targetTransform.moveWorld(m_directionalSpeed * deltaSec);
    targetTransform.rotate(glm::quat(m_angularSpeed * deltaSec));

    return targetTransform;
}

std::list<VoxelCollision> &Physics::move(float deltaSec) {
    updateSpeed(deltaSec);

    if (m_directionalSpeed != glm::vec3(0.0f) || m_angularSpeed != glm::vec3(0.0f)) {
        Transform targetTransform = projectedTransformIn(deltaSec);

        Movement movement(m_worldObject, m_worldObject.transform(), targetTransform);
        movement.perform();
    }

    return m_worldObject.collisionDetector().lastCollisions();
}

void Physics::accelerateDirectional(const glm::vec3& direction) {
    m_directionalAcceleration += m_worldObject.transform().orientation() * direction;
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
    m_directionalSpeed *= (1.f - m_directionalDampening * deltaSec);
    m_directionalSpeed += m_directionalAcceleration * deltaSec;

    m_angularSpeed *= (1.f - m_angularDampening * deltaSec);
    m_angularSpeed = m_angularSpeed + (m_angularAcceleration*deltaSec);

    m_directionalAcceleration = glm::vec3(0);
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


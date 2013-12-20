#include "physics.h"

#include <functional>
#include <iostream>

#include <glm/gtx/quaternion.hpp>

#include "worldtransform.h"

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
    m_dampening("physics.globalDampening"),
    m_angularDampening("physics.globalAngularDampening"),
    m_mass(0),
    m_accumulatedMassVec(0.0f, 0.0f, 0.0f),
    m_worldObject(worldObject)
{
    m_massScaleFactor = glm::pow(scale, 3.f);
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

std::list<VoxelCollision> &Physics::move(float deltaSec) {
    updateSpeed(deltaSec);

    if(m_speed != glm::vec3(0.0f) || m_angularSpeed != glm::vec3(0.0f)) {
        WorldTransform targetTransform(m_worldObject.transform());
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
    alterCell<std::plus>(voxel);
}

void Physics::removeVoxel(Voxel* voxel) {
    alterCell<std::minus>(voxel);
}

void Physics::updateSpeed(float deltaSec) {
    m_speed *= (1.f - m_dampening * deltaSec);
    m_speed += m_acceleration * deltaSec;

    m_angularSpeed *= (1.f - m_angularDampening * deltaSec);
    m_angularSpeed = m_angularSpeed + (m_angularAcceleration*deltaSec);

    m_acceleration = glm::vec3(0);
    m_angularAcceleration = glm::vec3(0);
}

template<template<typename> class Op>
void Physics::alterCell(Voxel* voxel) {
    float scaledVoxelMass = voxel->normalizedMass() * m_massScaleFactor;

    m_mass = Op<float>()(m_mass, scaledVoxelMass);
    m_accumulatedMassVec = Op<glm::vec3>()(m_accumulatedMassVec, static_cast<glm::vec3>(voxel->gridCell()) * scaledVoxelMass);
    m_worldObject.setCenterAndAdjustPosition(m_accumulatedMassVec / m_mass);
}


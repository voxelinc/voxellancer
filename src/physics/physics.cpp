#include "physics.h"

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
    m_center(0),
    m_massValid(true),
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

bool Physics::massValid() const {
    return m_massValid;
}

glm::vec3 Physics::calculateMassAndCenter() {
    if (m_massValid)
        m_center;

    glm::vec3 center;
    m_mass = 0;
    for (auto pair : m_worldObject.voxelMap()) {
        Voxel *voxel = pair.second;
        m_mass += voxel->mass();
        center += glm::vec3(voxel->gridCell()) * voxel->mass();
    }
    center /= m_mass;
    m_mass *= m_massScaleFactor;
    m_massValid = true;
    m_center = center;

    return m_center;
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
    Voxel * voxel = m_worldObject.voxel(position);

    float oldUnscaledMass = m_mass / m_massScaleFactor;
    float newUnscaledMass = oldUnscaledMass - voxel->mass();
    
    m_center -= glm::vec3(voxel->gridCell()) * voxel->mass() / oldUnscaledMass;
    m_center *= oldUnscaledMass / newUnscaledMass;

    m_mass -= voxel->mass() * m_massScaleFactor;
}

void Physics::updateSpeed(float deltaSec) {
    m_speed *= (1.f - m_dampening * deltaSec);
    m_speed += m_acceleration * deltaSec;

    m_angularSpeed *= (1.f - m_angularDampening * deltaSec);
    m_angularSpeed = m_angularSpeed + (m_angularAcceleration*deltaSec);

    m_acceleration = glm::vec3(0);
    m_angularAcceleration = glm::vec3(0);
}

glm::vec3 Physics::physicalCenter() {
    return m_center;
}





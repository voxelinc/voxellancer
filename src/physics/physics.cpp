#include "physics.h"

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
#include "movement.h"


Physics::Physics(WorldObject& worldObject, float scale):
    m_directionalDampening(Property<float>("physics.globalDirectionalDampening")),
    m_angularDampening(Property<float>("physics.globalAngularDampening")),
    m_mass(0),
    m_accumulatedMassVec(0.0f, 0.0f, 0.0f),
    m_worldObject(worldObject)
{
    m_massScaleFactor = glm::pow(scale, 3.f);
}

float Physics::directionalDampening() const {
    return m_directionalDampening;
}

void Physics::setDirectionalDampening(const Property<float>& directionalDampening) {
    m_directionalDampening = directionalDampening;
}

float Physics::angularDampening() const {
    return m_angularDampening;
}

void Physics::setAngularDampening(const Property<float>& angularDampening) {
    m_angularDampening = angularDampening;
}

const Speed& Physics::speed() const {
    return m_speed;
}

void Physics::setSpeed(const Speed& speed) {
    m_speed = speed;
}

const Acceleration& Physics::acceleration() const {
    return m_acceleration;
}

void Physics::setAcceleration(const Acceleration& acceleration) {
    m_acceleration = acceleration;
}

float Physics::mass() const {
    return m_mass;
}

const Transform Physics::projectedTransformIn(float deltaSec){
    Transform targetTransform(m_worldObject.transform());

    targetTransform.moveWorld(m_speed.directional() * deltaSec);
    targetTransform.rotateWorld(glm::quat(m_speed.angular() * deltaSec));

    return targetTransform;
}

std::list<VoxelCollision> &Physics::move(float deltaSec) {
    updateSpeed(deltaSec);

    if (m_speed.directional() != glm::vec3(0.0f) || m_speed.angular() != glm::vec3(0.0f)) {
        Transform targetTransform = projectedTransformIn(deltaSec);

        Movement movement(m_worldObject, m_worldObject.transform(), targetTransform);
        movement.perform();
    }

    return m_worldObject.collisionDetector().lastCollisions();
}

void Physics::addVoxel(Voxel* voxel) {
    voxelChanged(voxel, true);
}

void Physics::removeVoxel(Voxel* voxel) {
    voxelChanged(voxel, false);
}

void Physics::updateSpeed(float deltaSec) {
    glm::vec3 directional(m_speed.directional());
    glm::vec3 angular(m_speed.angular());

    directional *= (1.0f - m_directionalDampening * deltaSec);
    directional += m_acceleration.directional() * deltaSec;

    angular *= (1.0f - m_angularDampening * deltaSec);
    angular += m_acceleration.angular() * deltaSec;

    m_speed = Speed(directional, angular);

    m_acceleration.clear();
}

void Physics::voxelChanged(Voxel* voxel, bool isAdd) {
    float scaledVoxelMass = voxel->normalizedMass() * m_massScaleFactor;
    if (!isAdd) {
        scaledVoxelMass *= -1;
    }

    m_mass = m_mass + scaledVoxelMass;
    m_accumulatedMassVec = m_accumulatedMassVec + glm::vec3(voxel->gridCell()) * scaledVoxelMass;

    if (m_mass > 0.0f) {
        m_worldObject.transform().setCenterAndAdjustPosition(m_accumulatedMassVec / m_mass);
    }  else {
        m_worldObject.transform().setCenterAndAdjustPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    }
}


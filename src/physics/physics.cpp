#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include "physics.h"

#include "worldtransform.h"
#include "collision/collisiondetector.h"
#include "worldobject/worldobject.h"
#include "worldtree/worldtreegeode.h"
#include "world/world.h"
#include "worldtree/worldtree.h"


Physics::Physics(WorldObject & worldObject) :
    m_speed(0),
    m_angularSpeed(0),
    m_acceleration(0),
    m_angularAcceleration(0),
    m_dampening("physics.globalDampening"),
    m_angularDampening("physics.globalAngularDampening"),
    m_rotationFactor("physics.globalRotationFactor"),
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

std::list<Collision> &Physics::move(float deltaSec) {
    updateSpeed(deltaSec);

    m_movement.clear();
    m_movement.setOriginalTransform(m_worldObject.transform());
    m_movement.setDelta(deltaSec, m_speed, m_angularSpeed);
    m_movement.calculatePhases(m_worldObject.collisionDetector());

    applyTransform();

    return m_collisions;
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

// tries to apply the current transform as far as no collision happens.
// should not be used if the voxelcluster is not part of a worldTree.
void Physics::applyTransform() {
    m_worldObject.collisionDetector().reset();
    m_steps = 0;
  //  std::cout << this << " Phases: " << m_movement.movePhases().size() << ": ";
    for (MovePhase* movePhase : m_movement.movePhases()) {
     //   std::cout << "  stepped: " << movePhase->isStepped() << std::endl;
        if (movePhase->isStepped()) {
        //    std::cout << "Stepped " << movePhase->distance() << " | ";
            doSteppedTransform(*movePhase);
        }
        else {
           // std::cout << "Warp "<< movePhase->distance() << " | ";
            doWarpTransform(*movePhase);
        //    assert(m_worldObject.collisionDetector().checkCollisions().size() == 0);
        }

        if (m_worldObject.collisionDetector().lastCollisions().size() > 0) { // There's something in front of you, makes no sense to go further
            break;
        }
    }
    //std::cout << "total steps: " << ((float)m_steps/World::instance()->deltaSec()) << std::endl;
}

void Physics::doWarpTransform(const MovePhase& movePhase) {
    m_worldObject.transform().setPosition(movePhase.targetTransform().position());
    m_worldObject.transform().setOrientation(movePhase.targetTransform().orientation());
    m_worldObject.collisionDetector().updateGeode();
}

void Physics::doSteppedTransform(const MovePhase& movePhase) {
    for (int s = 0; s < movePhase.stepCount(); s++) { m_steps++;
        WorldTransform newTransform(movePhase.step(s));
        WorldTransform oldTransform = m_worldObject.transform();

        m_worldObject.transform().setOrientation(newTransform.orientation());
        m_worldObject.transform().setPosition(newTransform.position());
        m_worldObject.collisionDetector().updateGeode();

        const std::list<Collision>& collisions = m_worldObject.collisionDetector().checkCollisions();

        if(!collisions.empty()) {
            m_worldObject.transform().setOrientation(oldTransform.orientation());
            m_worldObject.transform().setPosition(oldTransform.position());
            m_worldObject.collisionDetector().updateGeode();
            break;
        }
    }
}




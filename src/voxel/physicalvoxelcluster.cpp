#include <glm/gtx/quaternion.hpp>
#include "physicalvoxelcluster.h"

#include "worldtransform.h"
#include "collision/collisiondetector.h"
#include <iostream>


PhysicalVoxelCluster::PhysicalVoxelCluster(float scale) :
    CollidableVoxelCluster(glm::vec3(0), scale),
    m_speed(0),
    m_angularSpeed(0),
    m_acceleration(0),
    m_angularAcceleration(0),
    m_dampening("physics.globaldampening"),
    m_angularDampening("physics.globalangulardampening"),
    m_rotationFactor("physics.globalrotationfactor"),
    m_mass(0),
    m_massValid(true)
{

}

// only neccessary for manually constructed voxelclusters, not if 
// the cluster is build from clusterstore
void PhysicalVoxelCluster::finishInitialization() {
    calculateMassAndCenter();
    CollidableVoxelCluster::finishInitialization();
}

PhysicalVoxelCluster::~PhysicalVoxelCluster() {
}

void PhysicalVoxelCluster::calculateMassAndCenter() {
    if (m_massValid)
        return;

    glm::vec3 center;
    m_mass = 0;
    for (auto pair : m_voxels) {
        Voxel *voxel = pair.second;
        m_mass += 1.0; // voxel.mass?
        center += glm::vec3(voxel->gridCell()) * 1.0f; // voxel.mass?
    }
    center /= m_mass;
    m_transform.setCenter(center);
    m_massValid = true;
}

std::list<Collision> &PhysicalVoxelCluster::move(float delta_sec) {
    m_oldTransform = m_newTransform = m_transform;
    m_collisionDetector->reset();

    m_speed *= (1.f - m_dampening * delta_sec);
    m_speed += m_acceleration * delta_sec;
    m_newTransform.moveWorld(m_speed * delta_sec);

    m_angularSpeed *= (1.f - m_angularDampening * delta_sec);
    m_angularSpeed = m_angularSpeed + (m_angularAcceleration*delta_sec);
    m_newTransform.rotate(glm::quat(m_angularSpeed*delta_sec));

    applyTransform();

    m_acceleration = glm::vec3(0);
    m_angularAcceleration = glm::vec3(0);

    // currently only one collision is handled and the collision is resolved
    // immediately. this can only be moved somewhere else as soon as there is a way
    // to resolve multiple collisions
    std::list<Collision> &collisions = m_collisionDetector->lastCollisions();
    if (!collisions.empty()) {
        resolveCollision(collisions.front(), delta_sec);
    }

    updateGeode();

    return m_collisionDetector->lastCollisions();
}

void PhysicalVoxelCluster::resolveCollision(Collision & c, float delta_sec) {
    PhysicalVoxelCluster * p1 = static_cast<PhysicalVoxelCluster*>(c.voxelClusterA());
    PhysicalVoxelCluster * p2 = static_cast<PhysicalVoxelCluster*>(c.voxelClusterB());
    
    // you didn't create the object with the store and forgot to call finishInitialization()!
    // or you removed Voxels... this case is not handled yet.
    assert(p1->m_massValid);
    assert(p2->m_massValid);
    
    assert(p1->m_mass > 0);
    assert(p2->m_mass > 0);

    glm::vec3 normal = glm::normalize(p1->m_transform.applyTo(glm::vec3(c.voxelA()->gridCell())) - p2->m_transform.applyTo(glm::vec3(c.voxelB()->gridCell())));

    // old speed at collision point
    glm::vec3 v1 = (p1->m_newTransform.applyTo(glm::vec3(c.voxelA()->gridCell())) - p1->m_oldTransform.applyTo(glm::vec3(c.voxelA()->gridCell()))) / delta_sec;
    glm::vec3 v2 = (p2->m_newTransform.applyTo(glm::vec3(c.voxelB()->gridCell())) - p2->m_oldTransform.applyTo(glm::vec3(c.voxelB()->gridCell()))) / delta_sec;

    // new speed
    glm::vec3 v1_ = ((p1->m_mass - p2->m_mass) * v1 + 2 * p2->m_mass*v2) / (p1->m_mass + p2->m_mass);
    glm::vec3 v2_ = ((p2->m_mass - p1->m_mass) * v2 + 2 * p1->m_mass*v1) / (p1->m_mass + p2->m_mass);

    // vector from collision to center
    glm::vec3 r1 = p1->transform().position() - p1->transform().applyTo(glm::vec3(c.voxelA()->gridCell()));
    glm::vec3 r2 = p2->transform().position() - p2->transform().applyTo(glm::vec3(c.voxelB()->gridCell()));

    //speed difference
    float vDiff = glm::abs(glm::length(v1 - v2));

    // new angular speed
    glm::vec3 w1_ = glm::inverse((p1->transform().orientation())) * (m_rotationFactor.get() * vDiff * (1.f / p1->m_mass) * glm::cross(normal, r1));
    glm::vec3 w2_ = glm::inverse((p2->transform().orientation())) * (m_rotationFactor.get() * vDiff * (1.f / p2->m_mass) * glm::cross(-normal, r2));
    
    p1->m_speed = v1_;
    p2->m_speed = v2_;
    p1->m_angularSpeed = w1_;
    p2->m_angularSpeed = w2_;
}


// tries to apply the current transform as far as no collision happens.
// should not be used if the voxelcluster is not part of a worldtree.
void PhysicalVoxelCluster::applyTransform() {
    assert(m_geode != nullptr);

    if (m_newTransform != m_oldTransform) {
        if (isCollisionPossible()) {
            doSteppedTransform();
        } else {
            m_transform = m_newTransform;
        }
    }
}

bool PhysicalVoxelCluster::isCollisionPossible() {
    // the geode aabb is still the old one, add it to the final aabb
    AABB fullAabb = aabb(m_oldTransform).united(aabb(m_newTransform));
    // is there someone else than yourself inside?
    auto possibleCollisions = m_worldTree->geodesInAABB(fullAabb);
    return possibleCollisions.size() > 1;
}

void PhysicalVoxelCluster::doSteppedTransform() {
    float steps = calculateStepCount(m_oldTransform, m_newTransform);

    for (int i = 0; i <= steps; i++) {
        m_transform.setOrientation(glm::mix(m_oldTransform.orientation(), m_newTransform.orientation(), i / steps));
        m_transform.setPosition(glm::mix(m_oldTransform.position(), m_newTransform.position(), i / steps));
        updateGeode();
        const std::list<Collision> & collisions = m_collisionDetector->checkCollisions();
        if (!collisions.empty()) {
            assert(i > 0); // you're stuck, hopefully doesn't happen!
            m_transform.setOrientation(glm::mix(m_oldTransform.orientation(), m_newTransform.orientation(), (i - 1) / steps));
            m_transform.setPosition(glm::mix(m_oldTransform.position(), m_newTransform.position(), (i - 1) / steps));
            break;
        }
    }
}

static float MAX_TRANSLATION_STEP_SIZE = 0.1f;
static float MAX_ANGLE_STEP_SIZE = 10.0f;

float PhysicalVoxelCluster::calculateStepCount(const WorldTransform & oldTransform, const WorldTransform & newTransform) {
    float distance = glm::length(newTransform.position() - oldTransform.position());
    float steps = glm::floor(distance / MAX_TRANSLATION_STEP_SIZE) + 1.f; // at least one!
    
    float angle = glm::angle(glm::inverse(newTransform.orientation()) * oldTransform.orientation());
    if (std::isfinite(angle)) // sometimes glm::angle returns INF for really small angles
        steps = glm::max(steps, glm::floor(angle / MAX_ANGLE_STEP_SIZE) + 1.f);
    
    return steps;
}

// accelerate along local axis
void PhysicalVoxelCluster::accelerate(glm::vec3 direction) {
    m_acceleration += m_transform.orientation() * direction;
}

// angular acceleration around local axis
void PhysicalVoxelCluster::accelerateAngular(glm::vec3 axis) {
    m_angularAcceleration += axis;
}

void PhysicalVoxelCluster::addVoxel(Voxel *voxel) {
    CollidableVoxelCluster::addVoxel(voxel);
    voxel->setVoxelCluster(this);
    m_massValid = false;
}

void PhysicalVoxelCluster::removeVoxel(const cvec3 &position) {
    CollidableVoxelCluster::removeVoxel(position);
    m_massValid = false;
    // it would be better to calculate incremental mass/center changes here
    // something like mass -= 1; center -= 1/mass * pos; center /= (mass-1)/mass; should work
    // but there should be tests to verify this! (1 = mass of voxel)
}

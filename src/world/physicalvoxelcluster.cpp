#include <glm/gtx/quaternion.hpp>
#include "physicalvoxelcluster.h"

#include "worldtransform.h"
#include "collision/collisiondetector.h"
#include <iostream>


PhysicalVoxelCluster::PhysicalVoxelCluster(float scale) :
    WorldTreeVoxelCluster(glm::vec3(0), scale),
    m_speed(0),
    m_angularSpeed(0),
    m_acceleration(0),
    m_angularAcceleration(0),
    m_dampening("physics.globaldampening"),
    m_angularDampening("physics.globalangulardampening"),
    m_rotationFactor("physics.globalrotationfactor"),
    m_mass(0),
    m_mass_valid(1)
{

}

PhysicalVoxelCluster::PhysicalVoxelCluster(const PhysicalVoxelCluster& other) :
    WorldTreeVoxelCluster(other),
    m_speed(0),
    m_angularSpeed(0),
    m_acceleration(0),
    m_angularAcceleration(0),
    m_dampening("physics.globaldampening"),
    m_angularDampening("physics.globalangulardampening"),
    m_rotationFactor("physics.globalrotationfactor"),
    m_mass(other.m_mass),
    m_mass_valid(other.m_mass_valid)
{

}

// only neccessary for manually constructed voxelclusters, not if 
// the cluster is build from clusterstore
void PhysicalVoxelCluster::finishInitialization() {
    calculateMassAndCenter();
    WorldTreeVoxelCluster::finishInitialization();
}

PhysicalVoxelCluster::~PhysicalVoxelCluster() {
    glow::debug("aaaaa");
}

void PhysicalVoxelCluster::calculateMassAndCenter() {
    if (m_mass_valid)
        return;

    glm::vec3 center;
    m_mass = 0;
    for (auto pair : m_voxel) {
        Voxel voxel = pair.second;
        m_mass += 1.0; // voxel.mass?
        center += glm::vec3(voxel.gridCell()) * 1.0f; // voxel.mass?
    }
    center /= m_mass;
    m_transform.setCenter(center);
    m_mass_valid = true;
}

void PhysicalVoxelCluster::update(float delta_sec) {
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

    const std::list<Collision> &collisions = m_collisionDetector->lastCollisions();
    if (!collisions.empty()) {
        handleCollision(collisions.front(), delta_sec);
    }

    updateGeode();
}

void PhysicalVoxelCluster::handleCollision(const Collision & c, float delta_sec) {
    // TODO remove consts from collision detector
    PhysicalVoxelCluster * p1 = static_cast<PhysicalVoxelCluster*>(const_cast<WorldTreeVoxelCluster*>(c.voxelClusterA()));
    PhysicalVoxelCluster * p2 = static_cast<PhysicalVoxelCluster*>(const_cast<WorldTreeVoxelCluster*>(c.voxelClusterB()));
    
    // you didn't create the object with the store and forgot to call finishInitialization()!
    // or you removed Voxels... this case is not handled yet.
    assert(p1->m_mass_valid);
    assert(p2->m_mass_valid);

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

    // new angular speed
    glm::vec3 w1_ = glm::inverse((p1->transform().orientation())) * (m_rotationFactor.get() * glm::cross(normal, r1));
    glm::vec3 w2_ = glm::inverse((p2->transform().orientation())) * (m_rotationFactor.get() * glm::cross(-normal, r2));
    
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
    if (possibleCollisions.size()>1)
        std::cout << possibleCollisions.size() << std::endl;
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

// angular acceleration along local axis
void PhysicalVoxelCluster::accelerate_angular(glm::vec3 axis) {
    m_angularAcceleration += axis;
}

void PhysicalVoxelCluster::addVoxel(const Voxel & voxel) {
    WorldTreeVoxelCluster::addVoxel(voxel);
    m_mass_valid = false;
}

void PhysicalVoxelCluster::removeVoxel(const cvec3 &position) {
    WorldTreeVoxelCluster::removeVoxel(position);
    m_mass_valid = false;
    // it would be better to calculate mass/center changes here
}

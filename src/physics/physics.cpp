#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include "physics.h"

#include "worldtransform.h"
#include "collision/collisiondetector.h"
#include "worldobject/worldobject.h"
#include "worldtree/worldtreegeode.h"
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
    if (m_massValid)
        return;

    glm::vec3 center;
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

std::list<Impact> &Physics::move(float delta_sec) {
    m_oldTransform = m_newTransform = m_worldObject.transform();
    m_worldObject.collisionDetector().reset();

    updateSpeed(delta_sec);

    m_newTransform.moveWorld(m_speed * delta_sec);
    m_newTransform.rotate(glm::quat(m_angularSpeed*delta_sec));

    applyTransform();

    m_acceleration = glm::vec3(0);
    m_angularAcceleration = glm::vec3(0);

    m_impacts.clear();
    // currently only one collision is handled and the collision is resolved
    // immediately. this can only be moved somewhere else as soon as there is a way
    // to resolve multiple collisions
    std::list<Collision> &collisions = m_worldObject.collisionDetector().lastCollisions();
    if (!collisions.empty()) {
        resolveCollision(collisions.front(), delta_sec);
    }

    m_worldObject.collisionDetector().updateGeode();

    return m_impacts;
}

void Physics::updateSpeed(float delta_sec){
    m_speed *= (1.f - m_dampening * delta_sec);
    m_speed += m_acceleration * delta_sec;

    m_angularSpeed *= (1.f - m_angularDampening * delta_sec);
    m_angularSpeed = m_angularSpeed + (m_angularAcceleration*delta_sec);
}

void Physics::resolveCollision(Collision & c, float delta_sec) {
    WorldObject * wo1 = c.a().worldObject();
    WorldObject * wo2 = c.b().worldObject();

    Physics &p1 = wo1->physics();
    Physics &p2 = wo2->physics();

    // you didn't create the object with the store and forgot to call finishInitialization()!
    // or you removed Voxels... this case is not handled yet.

    assert(p1.m_massValid); assert(p2.m_massValid);
    assert(p1.m_mass > 0); assert(p2.m_mass > 0);

    glm::vec3 normal = glm::normalize(wo1->transform().applyTo(glm::vec3(c.a().voxel()->gridCell())) - wo2->transform().applyTo(glm::vec3(c.b().voxel()->gridCell())));

    // old speed at collision point
    glm::vec3 v1 = (p1.m_newTransform.applyTo(glm::vec3(c.a().voxel()->gridCell())) - p1.m_oldTransform.applyTo(glm::vec3(c.a().voxel()->gridCell()))) / delta_sec;
    glm::vec3 v2 = (p2.m_newTransform.applyTo(glm::vec3(c.b().voxel()->gridCell())) - p2.m_oldTransform.applyTo(glm::vec3(c.b().voxel()->gridCell()))) / delta_sec;

    // new speed
    glm::vec3 v1_ = ((p1.m_mass - p2.m_mass) * v1 + 2 * p2.m_mass*v2) / (p1.m_mass + p2.m_mass);
    glm::vec3 v2_ = ((p2.m_mass - p1.m_mass) * v2 + 2 * p1.m_mass*v1) / (p1.m_mass + p2.m_mass);

    // vector from collision to center
    glm::vec3 r1 = wo1->transform().position() - wo1->transform().applyTo(glm::vec3(c.a().voxel()->gridCell()));
    glm::vec3 r2 = wo2->transform().position() - wo2->transform().applyTo(glm::vec3(c.b().voxel()->gridCell()));

    //speed difference
    float vDiff = glm::abs(glm::length(v1 - v2));

    // new angular speed
    glm::vec3 w1_ = glm::inverse((wo1->transform().orientation())) * (m_rotationFactor.get() * vDiff * (1.f / p1.m_mass) * glm::cross(normal, r1));
    glm::vec3 w2_ = glm::inverse((wo2->transform().orientation())) * (m_rotationFactor.get() * vDiff * (1.f / p2.m_mass) * glm::cross(-normal, r2));

    p1.m_speed = v1_;
    p2.m_speed = v2_;
    p1.m_angularSpeed = w1_;
    p2.m_angularSpeed = w2_;

    m_impacts.push_back(Impact(wo1, c.a().voxel(), glm::inverse(wo1->transform().orientation()) * (v2 - v1)));
    m_impacts.push_back(Impact(wo2, c.b().voxel(), glm::inverse(wo2->transform().orientation()) * (v1 - v2)));
}


// tries to apply the current transform as far as no collision happens.
// should not be used if the voxelcluster is not part of a worldTree.
void Physics::applyTransform() {
    if (m_newTransform != m_oldTransform) {
        if (isCollisionPossible()) {
            doSteppedTransform();
        } else {
            m_worldObject.transform().setPosition(m_newTransform.position());
            m_worldObject.transform().setOrientation(m_newTransform.orientation());
        }
    }
}

bool Physics::isCollisionPossible() {
    // the geode aabb is still the old one, add it to the final aabb
    AABB fullAabb = m_worldObject.collisionDetector().aabb(m_oldTransform).united(m_worldObject.collisionDetector().aabb(m_newTransform));
    // is there someone else than yourself inside?
    auto possibleCollisions = m_worldObject.collisionDetector().worldTree()->geodesInAABB(fullAabb);
    return possibleCollisions.size() > 1;
}


void Physics::doSteppedTransform() {
    float steps = calculateStepCount(m_oldTransform, m_newTransform);

    for (int i = 0; i <= steps; i++) {
        m_worldObject.transform().setOrientation(glm::slerp(m_oldTransform.orientation(), m_newTransform.orientation(), i / steps));
        m_worldObject.transform().setPosition(glm::mix(m_oldTransform.position(), m_newTransform.position(), i / steps));
        m_worldObject.collisionDetector().updateGeode();
        const std::list<Collision> & collisions = m_worldObject.collisionDetector().checkCollisions();
        if (!collisions.empty()) {
            assert(i > 0); // you're stuck, hopefully doesn't happen!
            m_worldObject.transform().setOrientation(glm::slerp(m_oldTransform.orientation(), m_newTransform.orientation(), (i - 1) / steps));
            m_worldObject.transform().setPosition(glm::mix(m_oldTransform.position(), m_newTransform.position(), (i - 1) / steps));
            assert(std::isfinite(m_worldObject.transform().orientation().x));
            break;
        }
    }
}

static float MAX_TRANSLATION_STEP_SIZE = 0.1f;
static float MAX_ANGLE_STEP_SIZE = 10.0f;

float Physics::calculateStepCount(const WorldTransform & oldTransform, const WorldTransform & newTransform) {
    float distance = glm::length(newTransform.position() - oldTransform.position());
    float steps = std::max(glm::floor(distance / MAX_TRANSLATION_STEP_SIZE), 1.f); // at least one!


    float angle = glm::angle(glm::inverse(newTransform.orientation()) * oldTransform.orientation());
    if (std::isfinite(angle)) // sometimes glm::angle returns INF for really small angles
        steps = glm::max(steps, glm::floor(angle / MAX_ANGLE_STEP_SIZE) + 1.f);

    return steps;
}

// accelerate along local axis
void Physics::accelerate(glm::vec3 direction) {
    m_acceleration += m_worldObject.transform().orientation() * direction;
}

// angular acceleration around local axis
void Physics::accelerateAngular(glm::vec3 axis) {
    m_angularAcceleration += axis;
}

void Physics::addVoxel(Voxel *voxel) {
    m_massValid = false;
}

void Physics::removeVoxel(const glm::ivec3 &position) {
    m_massValid = false;
    calculateMassAndCenter();
    //m_worldObject.transform().setPosition(-oldCenter + m_worldObject.transform().center());
    // it would be better to calculate incremental mass/center changes here
    // something like mass -= 1; center -= 1/mass * pos; center /= (mass-1)/mass; should work
    // but there should be tests to verify this! (1 = mass of voxel)
}

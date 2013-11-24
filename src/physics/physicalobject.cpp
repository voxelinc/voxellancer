#include <glm/gtx/quaternion.hpp>

#include "physicalobject.h"
#include "worldtransform.h"
#include "collision/collisiondetector.h"


PhysicalObject::PhysicalObject(float scale):
    VoxelCluster(glm::vec3(0), scale),
    m_speed(0),
    m_angularSpeed(),
    m_acceleration(0),
    m_angularAcceleration(),
    m_dampening("physics.globaldampening", 0.5f),
    m_angularDampening("physics.globalangulardampening", 0.8f),
    m_rotationFactor("physics.globalrotationfactor", 0.1f),
    m_mass(0)
{

}

PhysicalObject::~PhysicalObject() {

}

void PhysicalObject::calculateMassAndCenter() {
    glm::vec3 center;
    for (auto pair : m_voxel) {
        Voxel voxel = pair.second;
        m_mass += 1.0; // voxel.mass 
        center += glm::vec3(voxel.gridCell()) * 1.0f; // voxel.mass
    }
    center /= m_mass;
    m_transform.setCenter(center);
}

void PhysicalObject::update(float delta_sec) {
    m_delta_sec = delta_sec;
    m_oldTransform = m_newTransform = m_transform;
    
    m_speed *= (1.f - m_dampening * delta_sec);
    m_speed += m_acceleration * delta_sec;
    m_newTransform.moveWorld(m_speed * delta_sec);

    m_angularSpeed *= (1.f - m_angularDampening * delta_sec);
    m_angularSpeed = m_angularSpeed + (m_angularAcceleration*delta_sec);

    m_newTransform.rotate(glm::quat(m_angularSpeed*delta_sec));

    applyTransform();

    m_acceleration = glm::vec3(0);
    m_angularAcceleration = glm::vec3(0);
}

void PhysicalObject::handleCollision(const Collision & c) {
    // TODO remove consts from collision detector
    PhysicalObject * p1 = static_cast<PhysicalObject*>(const_cast<VoxelCluster*>(c.voxelA()->voxelCluster()));
    PhysicalObject * p2 = static_cast<PhysicalObject*>(const_cast<VoxelCluster*>(c.voxelB()->voxelCluster()));

    glm::vec3 v1 = (p1->m_newTransform.applyTo(glm::vec3(c.voxelA()->gridCell())) - p1->m_oldTransform.applyTo(glm::vec3(c.voxelA()->gridCell()))) / m_delta_sec;
    glm::vec3 v2 = (p2->m_newTransform.applyTo(glm::vec3(c.voxelB()->gridCell())) - p2->m_oldTransform.applyTo(glm::vec3(c.voxelB()->gridCell()))) / m_delta_sec;

    glm::vec3 v1_ = ((p1->m_mass - p2->m_mass) * v1 + 2 * p2->m_mass*v2) / (p1->m_mass + p2->m_mass);
    glm::vec3 v2_ = ((p2->m_mass - p1->m_mass) * v2 + 2 * p1->m_mass*v1) / (p1->m_mass + p2->m_mass);

    glm::vec3 r1 =  -p1->transform().applyTo(glm::vec3(c.voxelA()->gridCell())) + p1->transform().position();
    glm::vec3 r2 = -p2->transform().applyTo(glm::vec3(c.voxelB()->gridCell())) + p2->transform().position();

    p1->m_angularSpeed = glm::inverse(p1->transform().orientation()) * (m_rotationFactor.get() * glm::cross(v1_, r1));
    p2->m_angularSpeed = glm::inverse(p2->transform().orientation()) * (m_rotationFactor.get() * glm::cross(v2_, r2));

    p1->m_speed = v1_;
    p2->m_speed = v2_;
}


// tries to apply the current transform as far as no collision happens.
// should not be used if the voxelcluster is not part of a worldtree.
void PhysicalObject::applyTransform(bool checkCollision) {
    if (checkCollision) {
        assert(m_geode != nullptr);

        if (m_newTransform != m_oldTransform) {
            if (isCollisionPossible()) {
                doSteppedTransform();
            } else {
                m_transform = m_newTransform;
            }
        }
    }
    updateGeode();
}

bool PhysicalObject::isCollisionPossible() {
    // the geode aabb is still the old one, add it to the final aabb
    AABB fullAabb = m_geode->aabb().united(aabb());
    // is there someone else than yourself inside?
    return m_worldTree->geodesInAABB(fullAabb).size() > 1;
}

void PhysicalObject::doSteppedTransform() {
    float steps = calculateStepCount(m_oldTransform, m_newTransform);

    CollisionDetector collisionDetector(*m_worldTree, *this);

    for (int i = 0; i <= steps; i++) {
        m_transform.setOrientation(glm::mix(m_oldTransform.orientation(), m_newTransform.orientation(), i / steps));
        m_transform.setPosition(glm::mix(m_oldTransform.position(), m_newTransform.position(), i / steps));
        updateGeode();
        const std::list<Collision> & collisions = collisionDetector.checkCollisions();
        if (!collisions.empty()) {
            assert(i > 0); // you're stuck, hopefully doesn't happen!
            m_transform.setOrientation(glm::mix(m_oldTransform.orientation(), m_newTransform.orientation(), (i - 1) / steps));
            m_transform.setPosition(glm::mix(m_oldTransform.position(), m_newTransform.position(), (i - 1) / steps));
            handleCollision(collisions.front());
            break;
        }
    }
}

static float MAX_TRANSLATION_STEP_SIZE = 0.1f;
static float MAX_ANGLE_STEP_SIZE = 10.0f;

float PhysicalObject::calculateStepCount(const WorldTransform & oldTransform, const WorldTransform & newTransform) {
    float distance = glm::length(newTransform.position() - oldTransform.position());
    float angle = glm::angle(glm::inverse(newTransform.orientation()) * oldTransform.orientation());
    float steps = glm::floor(distance / MAX_TRANSLATION_STEP_SIZE) + 1.f; // at least one!
    steps = glm::max(steps, glm::floor(angle / MAX_ANGLE_STEP_SIZE) + 1.f);
    return steps;
}

// accelerate along local axis
void PhysicalObject::accelerate(glm::vec3 direction) {
    m_acceleration += m_transform.orientation() * direction;
}

void PhysicalObject::accelerate_angular(glm::vec3 axis) {
    m_angularAcceleration += axis;
}

#include <glm/gtx/quaternion.hpp>

#include "physicalobject.h"
#include "worldtransform.h"
#include "collision/collisiondetector.h"


PhysicalObject::PhysicalObject(float scale):
    VoxelCluster(glm::vec3(0), scale),
    m_speed(0),
    m_angular_speed(),
    m_acceleration(0),
    m_angular_acceleration(),
    m_dampening("physics.globaldampening", 0.3f),
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
    m_speed *= (1.f - m_dampening * delta_sec);
    m_speed += m_acceleration * delta_sec;
    m_transform.moveWorld(m_speed * delta_sec);

    m_angular_speed = glm::pow(m_angular_speed, (1.f - m_dampening * delta_sec));
    m_angular_speed = m_angular_speed * glm::pow(m_angular_acceleration, delta_sec);
    m_transform.rotateWorld(glm::pow(m_angular_speed, delta_sec));

    applyTransform();

    m_acceleration = glm::vec3(0);
    m_angular_acceleration = glm::quat();
}

void PhysicalObject::handleCollision(const Collision & c) {
    // TODO remove consts from collision detector
    PhysicalObject * p1 = static_cast<PhysicalObject*>(const_cast<VoxelCluster*>(c.voxelA()->voxelCluster()));
    PhysicalObject * p2 = static_cast<PhysicalObject*>(const_cast<VoxelCluster*>(c.voxelB()->voxelCluster()));

    glm::vec3 v1 = ((p1->m_mass - p2->m_mass) * p1->m_speed + 2 * p2->m_mass*p2->m_speed) / (p1->m_mass + p2->m_mass);
    glm::vec3 v2 = ((p2->m_mass - p1->m_mass) * p2->m_speed + 2 * p1->m_mass*p1->m_speed) / (p1->m_mass + p2->m_mass);

    p1->m_speed = v1;
    p2->m_speed = v2;
}


// tries to apply the current transform as far as no collision happens.
// should not be used if the voxelcluster is not part of a worldtree.
void PhysicalObject::applyTransform(bool checkCollision) {
    if (checkCollision) {
        assert(m_geode != nullptr);

        bool sthChanged = m_transform.position() != m_oldTransform.position();
        sthChanged |= m_transform.orientation() != m_oldTransform.orientation();
        if (sthChanged) {
            if (isCollisionPossible())
                doSteppedTransform();
        }
    }
    m_oldTransform = m_transform;
    updateGeode();
}

bool PhysicalObject::isCollisionPossible() {
    // the geode aabb is still the old one, add it to the final aabb
    AABB fullAabb = m_geode->aabb().united(aabb());
    // is there someone else than yourself inside?
    return m_worldTree->geodesInAABB(fullAabb).size() > 1;
}

void PhysicalObject::doSteppedTransform() {
    float steps = calculateStepCount();

    WorldTransform new_transform = m_transform;
    CollisionDetector collisionDetector(*m_worldTree, *this);

    for (int i = 0; i <= steps; i++) {
        m_transform.setOrientation(glm::mix(m_oldTransform.orientation(), new_transform.orientation(), i / steps));
        m_transform.setPosition(glm::mix(m_oldTransform.position(), new_transform.position(), i / steps));
        updateGeode();
        const std::list<Collision> & collisions = collisionDetector.checkCollisions();
        if (!collisions.empty()) {
            assert(i > 0); // you're stuck, hopefully doesn't happen!
            m_transform.setOrientation(glm::mix(m_oldTransform.orientation(), new_transform.orientation(), (i - 1) / steps));
            m_transform.setPosition(glm::mix(m_oldTransform.position(), new_transform.position(), (i - 1) / steps));
            handleCollision(collisions.front());
            break;
        }
    }
}

static float MAX_TRANSLATION_STEP_SIZE = 0.1f;
static float MAX_ANGLE_STEP_SIZE = 10.0f;

float PhysicalObject::calculateStepCount() {
    float distance = glm::length(m_transform.position() - m_oldTransform.position());
    float angle = glm::degrees(2 * glm::acos(glm::dot(m_transform.orientation(), m_oldTransform.orientation())));
    float steps = glm::floor(distance / MAX_TRANSLATION_STEP_SIZE) + 1.f; // at least one!
    steps = glm::max(steps, glm::floor(angle / MAX_ANGLE_STEP_SIZE) + 1.f);
    return steps;
}

// accelerate along local axis
void PhysicalObject::accelerate(glm::vec3 direction) {
    m_acceleration += m_transform.orientation() * direction;
}

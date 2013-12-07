#include "impactresolver.h"

#include <cassert>

#include "worldobject/worldobject.h"

#include "world/helper/impact.h"


void ImpactResolver::alterVelocities(std::list<Impact> &allImpacts) {
    calculateImpactsPerWorldObject(allImpacts);

    for(auto p : m_impactsPerWordObject) {
        assert(p.first != nullptr && !p.second.empty());

        alterVelocity(p.first, p.second.front());
    }
}
//
//    // currently only one collision is handled and the collision is resolved
//    // immediately. this can only be moved somewhere else as soon as there is a way
    // to resolve multiple collisions

void ImpactResolver::calculateImpactsPerWorldObject(const std::list<Impact> &allImpacts) {

}

void ImpactResolver::alterVelocity(WorldObject* worldObject, const Impact& impact) {

}

//void Physics::resolveCollision(Collision & c, float delta_sec) {
//    WorldObject * wo1 = c.a().worldObject();
//    WorldObject * wo2 = c.b().worldObject();
//
//    Physics &p1 = wo1->physics();
//    Physics &p2 = wo2->physics();
//
//    // you didn't create the object with the store and forgot to call finishInitialization()!
//    // or you removed Voxels... this case is not handled yet.
//    assert(p1.m_massValid); assert(p2.m_massValid);
//    assert(p1.m_mass > 0); assert(p2.m_mass > 0);
//
//    glm::vec3 normal = glm::normalize(wo1->transform().applyTo(glm::vec3(c.a().voxel()->gridCell())) - wo2->transform().applyTo(glm::vec3(c.b().voxel()->gridCell())));
//
//    // old speed at collision point
//    glm::vec3 v1 = (p1.m_newTransform.applyTo(glm::vec3(c.a().voxel()->gridCell())) - p1.m_oldTransform.applyTo(glm::vec3(c.a().voxel()->gridCell()))) / delta_sec;
//    glm::vec3 v2 = (p2.m_newTransform.applyTo(glm::vec3(c.b().voxel()->gridCell())) - p2.m_oldTransform.applyTo(glm::vec3(c.b().voxel()->gridCell()))) / delta_sec;
//
//    // new speed
//    glm::vec3 v1_ = ((p1.m_mass - p2.m_mass) * v1 + 2 * p2.m_mass*v2) / (p1.m_mass + p2.m_mass);
//    glm::vec3 v2_ = ((p2.m_mass - p1.m_mass) * v2 + 2 * p1.m_mass*v1) / (p1.m_mass + p2.m_mass);
//
//    // vector from collision to center
//    glm::vec3 r1 = wo1->transform().position() - wo1->transform().applyTo(glm::vec3(c.a().voxel()->gridCell()));
//    glm::vec3 r2 = wo2->transform().position() - wo2->transform().applyTo(glm::vec3(c.b().voxel()->gridCell()));
//
//    //speed difference
//    float vDiff = glm::abs(glm::length(v1 - v2));
//
//    // new angular speed
//    glm::vec3 w1_ = glm::inverse((wo1->transform().orientation())) * (m_rotationFactor.get() * vDiff * (1.f / p1.m_mass) * glm::cross(normal, r1));
//    glm::vec3 w2_ = glm::inverse((wo2->transform().orientation())) * (m_rotationFactor.get() * vDiff * (1.f / p2.m_mass) * glm::cross(-normal, r2));
//
//    p1.m_speed = v1_;
//    p2.m_speed = v2_;
//    p1.m_angularSpeed = w1_;
//    p2.m_angularSpeed = w2_;
//
//    m_impacts.push_back(Impact(wo1, c.a().voxel(), glm::inverse(wo1->transform().orientation()) * (v2 - v1)));
//    m_impacts.push_back(Impact(wo2, c.b().voxel(), glm::inverse(wo2->transform().orientation()) * (v1 - v2)));
//}

//
//    std::list<Collision> &collisions = m_worldObject.collisionDetector().lastCollisions();
//    if (!collisions.empty()) {
//        resolveCollision(collisions.front(), delta_sec);
//    }

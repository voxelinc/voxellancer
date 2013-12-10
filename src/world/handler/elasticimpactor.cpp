#include "elasticimpactor.h"

#include "worldobject/worldobject.h"

#include "physics/physics.h"

#include "utils/tostring.h"


void ElasticImpactor::parse(std::list<Impact>& worldObjectImpacts) {
    for(Impact& worldObjectImpact : worldObjectImpacts) {
        WorldObject* worldObject = worldObjectImpact.worldObject();
        Physics& physics = worldObject->physics();

        assert(physics.massValid());
        assert(physics.mass() > 0);

        WorldTransform targetTransform(worldObject->transform());
        targetTransform.moveWorld(physics.speed());
        targetTransform.rotate(glm::quat(physics.angularSpeed()));

        glm::vec3 v1 = targetTransform.applyTo(glm::vec3(worldObjectImpact.voxel()->gridCell())) - worldObject->transform().applyTo(glm::vec3(worldObjectImpact.voxel()->gridCell()));
        glm::vec3 v2 = worldObjectImpact.speed();
        float m1 = physics.mass();
        float m2 = worldObjectImpact.mass();

        physics.setSpeed(((m1 - m2) * v1 + 2.0f * v2 * m2) / (m1 + m2));

//
//        glm::vec3 normal = glm::normalize(wo1->transform().applyTo(glm::vec3(c.a().voxel()->gridCell())) - wo2->transform().applyTo(glm::vec3(c.b().voxel()->gridCell())));
//        float vDiff = glm::abs(glm::length(v1 - v2));
//        glm::vec3 r1 = wo1->transform().position() - wo1->transform().applyTo(glm::vec3(c.a().voxel()->gridCell()));
//
//        glm::vec3 w1_ = glm::inverse((worldObject->transform().orientation())) * (physics().rotationFactor.get() * vDiff * (1.f / m1) * glm::cross(normal, r1));
//
//
//
//        // you didn't create the object with the store and forgot to call finishInitialization()!
//        // or you removed Voxels... this case is not handled yet.
//

//        // old speed at collision point
//        glm::vec3 v1 = (p1.m_newTransform.applyTo(glm::vec3(c.a().voxel()->gridCell())) - p1.m_oldTransform.applyTo(glm::vec3(c.a().voxel()->gridCell()))) / delta_sec;
//        glm::vec3 v2 = (p2.m_newTransform.applyTo(glm::vec3(c.b().voxel()->gridCell())) - p2.m_oldTransform.applyTo(glm::vec3(c.b().voxel()->gridCell()))) / delta_sec;
//
//        // new speed
//        glm::vec3 v1_ = ((p1.m_mass - p2.m_mass) * v1 + 2 * p2.m_mass*v2) / (p1.m_mass + p2.m_mass);
//        glm::vec3 v2_ = ((p2.m_mass - p1.m_mass) * v2 + 2 * p1.m_mass*v1) / (p1.m_mass + p2.m_mass);
//
//        // vector from collision to center
//        glm::vec3 r1 = wo1->transform().position() - wo1->transform().applyTo(glm::vec3(c.a().voxel()->gridCell()));
//        glm::vec3 r2 = wo2->transform().position() - wo2->transform().applyTo(glm::vec3(c.b().voxel()->gridCell()));
//
//        //speed difference
//        float vDiff = glm::abs(glm::length(v1 - v2));
//
//        // new angular speed
//        glm::vec3 w1_ = glm::inverse((wo1->transform().orientation())) * (m_rotationFactor.get() * vDiff * (1.f / p1.m_mass) * glm::cross(normal, r1));
//        glm::vec3 w2_ = glm::inverse((wo2->transform().orientation())) * (m_rotationFactor.get() * vDiff * (1.f / p2.m_mass) * glm::cross(-normal, r2));
//
//        p1.m_speed = v1_;
//        p2.m_speed = v2_;
//        p1.m_angularSpeed = w1_;
//        p2.m_angularSpeed = w2_;
//
//        m_impacts.push_back(Impact(wo1, c.a().voxel(), glm::inverse(wo1->transform().orientation()) * (v2 - v1)));
//        m_impacts.push_back(Impact(wo2, c.b().voxel(), glm::inverse(wo2->transform().orientation()) * (v1 - v2)));
    }
}


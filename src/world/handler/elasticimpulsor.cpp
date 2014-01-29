#include "elasticimpulsor.h"

#include "worldobject/worldobject.h"

#include "physics/physics.h"

#include "utils/tostring.h"


ElasticImpulsor::ElasticImpulsor():
    m_rotationFactor("physics.globalRotationFactor")
{
}

void ElasticImpulsor::parse(std::list<Impulse>& worldObjectImpulses) {
    for(Impulse& worldObjectImpulse : worldObjectImpulses) {
        WorldObject* worldObject = worldObjectImpulse.worldObject();
        Physics& physics = worldObject->physics();

        assert(physics.mass() > 0);

        Transform targetTransform(worldObject->transform(), physics.speed(), glm::quat(physics.angularSpeed()));

        glm::vec3 v1 = targetTransform.applyTo(glm::vec3(worldObjectImpulse.voxel()->gridCell())) - worldObject->transform().applyTo(glm::vec3(worldObjectImpulse.voxel()->gridCell()));
        glm::vec3 v2 = worldObjectImpulse.speed();
        float m1 = physics.mass();
        float m2 = worldObjectImpulse.mass();

        physics.setSpeed(((m1 - m2) * v1 + 2.0f * v2 * m2) / (m1 + m2));

        glm::vec3 normal = worldObjectImpulse.normal();
        glm::vec3 r = worldObject->transform().position() - worldObject->transform().applyTo(glm::vec3(worldObjectImpulse.voxel()->gridCell()));
        float vDiff = glm::abs(glm::length(v1 - v2));

        physics.setAngularSpeed(glm::inverse((worldObject->transform().orientation())) * (m_rotationFactor.get() * vDiff * (1.f / m1) * glm::cross(normal, r)));
    }
}


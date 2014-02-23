#include "elasticimpulsor.h"

#include "worldobject/worldobject.h"

#include "physics/physics.h"

#include "utils/tostring.h"
#include "physics/impulse.h"
#include "voxel/voxel.h"


ElasticImpulsor::ElasticImpulsor():
    m_rotationFactor("physics.globalRotationFactor")
{
}

void ElasticImpulsor::parse(std::list<Impulse>& worldObjectImpulses) {
    for(Impulse& worldObjectImpulse : worldObjectImpulses) {
        WorldObject* worldObject = worldObjectImpulse.worldObject();
        Physics& physics = worldObject->physics();

        assert(physics.mass() > 0);

        Transform targetTransform(worldObject->transform(), physics.speed().directional(), glm::quat(physics.speed().angular()));

        glm::vec3 v1 = targetTransform.applyTo(glm::vec3(worldObjectImpulse.voxel()->gridCell())) - worldObject->transform().applyTo(glm::vec3(worldObjectImpulse.voxel()->gridCell()));
        glm::vec3 v2 = worldObjectImpulse.speed();
        float m1 = physics.mass();
        float m2 = worldObjectImpulse.mass();

        glm::vec3 directional(((m1 - m2) * v1 + 2.0f * v2 * m2) / (m1 + m2));

        glm::vec3 normal = worldObjectImpulse.normal();
        glm::vec3 r = worldObject->transform().position() - worldObject->transform().applyTo(glm::vec3(worldObjectImpulse.voxel()->gridCell()));
        float vDiff = glm::abs(glm::length(v1 - v2));

        glm::vec3 angular(m_rotationFactor.get() * vDiff * (1.f / m1) * glm::cross(normal, r));

        physics.setSpeed(Speed(directional, angular));
    }
}


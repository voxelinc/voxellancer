#include "impulsor.h"

#include "worldobject/worldobject.h"

#include "physics/physics.h"

#include "utils/tostring.h"
#include "physics/impulse.h"
#include "voxel/voxel.h"


Impulsor::Impulsor():
    m_rotationFactor("physics.rotationFactor"),
    m_elasticity("physics.elasticity")
{
}

void Impulsor::parse(std::list<Impulse>& worldObjectImpulses) {
    for(Impulse& worldObjectImpulse : worldObjectImpulses) {
        WorldObject* worldObject = worldObjectImpulse.worldObject();
        Physics& physics = worldObject->physics();

        assert(physics.mass() > 0);

        Transform targetTransform = physics.speed().moved(worldObject->transform(), 1.0f);

        glm::vec3 v1 = targetTransform.applyTo(glm::vec3(worldObjectImpulse.voxel()->gridCell())) - worldObjectImpulse.voxel()->position();
        glm::vec3 v2 = worldObjectImpulse.speed();
        float m1 = physics.mass();
        float m2 = worldObjectImpulse.mass();
        float k = m_elasticity;

        glm::vec3 directional((m1*v1 + m2*v2 - m2 * (v1 - v2) * k) / (m1 + m2)); // See partly elastic impulse

        glm::vec3 normal = worldObjectImpulse.normal();
        glm::vec3 r = worldObject->transform().position() - worldObject->transform().applyTo(glm::vec3(worldObjectImpulse.voxel()->gridCell()));
        float vDiff = glm::abs(glm::length(v1 - v2));

        glm::vec3 angular(m_rotationFactor.get() * vDiff * (1.f / m1) * glm::cross(normal, r)); // Some magic to produce rotation

        physics.setSpeed(Speed(directional, angular));
    }
}


#include "voxelparticlesetup.h"

#include <glm/gtx/quaternion.hpp>


VoxelParticleSetup::VoxelParticleSetup(const Transform& transform, const Visuals& visuals, const Speed& speed, float lifetime):
    m_transform(transform),
    m_visuals(visuals),
    m_speed(speed),
    m_lifetime(lifetime)
{
}

VoxelParticleData VoxelParticleSetup::toData(float timeSecs) const {
    VoxelParticleData particle;

    particle.creationPosition = m_transform.position();
    particle.creationEulers = glm::eulerAngles(m_transform.orientation());
    particle.directionalSpeed = m_speed.directional();
    particle.angularSpeed = m_speed.angular();
    particle.creationTime = timeSecs;
    particle.deathTime = timeSecs + m_lifetime;
    particle.scale = m_transform.scale();
    particle.color = m_visuals.color();
    particle.emissiveness = m_visuals.emissiveness();

    return particle;
}


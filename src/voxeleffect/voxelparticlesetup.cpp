#include "voxelparticlesetup.h"

#include <glm/gtx/quaternion.hpp>


VoxelParticleSetup::VoxelParticleSetup(const Transform& transform, const Visuals& visuals, const Speed& speed,
                                       float directionalDampening, float angularDampening, float lifetime):
    m_transform(transform),
    m_visuals(visuals),
    m_speed(speed),
    m_directionalDampening(directionalDampening),
    m_angularDampening(angularDampening),
    m_lifetime(lifetime)
{
}

VoxelParticleData VoxelParticleSetup::toData(float timeSecs) const {
    return VoxelParticleData (
        m_transform.position(),
        glm::eulerAngles(m_transform.orientation()),
        m_speed.directional(),
        m_speed.angular(),
        timeSecs,
        timeSecs + m_lifetime,
        m_transform.scale(),
        m_visuals.color(),
        m_visuals.emissiveness(),
        m_directionalDampening,
        m_angularDampening
    );
}


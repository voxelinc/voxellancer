#include "voxelparticlespawnbase.h"

#include <ctime>

#include "world/god.h"
#include "world/world.h"
#include "utils/randvec.h"
#include "utils/randfloat.h"
#include "utils/randbool.h"

#include "voxelparticledata.h"
#include "voxelparticlesetup.h"
#include "voxelparticleengine.h"


VoxelParticleSpawnBase::VoxelParticleSpawnBase(char* dampeningName,
                       char* angularDampeningName,
                       char* baseForceName,
                       char* angularBaseForceName) :
    m_position(0, 0, 0),
    m_scale(1.0f),
    m_scaleRandomization(0.0f),
    m_force(1.0f),
    m_forceRandomization(0.0f),
    m_lifetime(1.0f),
    m_lifetimeRandomization(0.0f),
    m_color(0xFFFFFF),
    m_emissiveness(0.0f),
    m_impactVector(0, 0, 0),
    m_particleDampening(dampeningName),
    m_particleAngularDampening(angularDampeningName),
    m_particleBaseForce(baseForceName),
    m_particleAngularBaseForce(angularBaseForceName)
{
}

void VoxelParticleSpawnBase::setPosition(const glm::vec3& position) {
    m_position = position;
}

void VoxelParticleSpawnBase::setScale(float scale, float randomization) {
    assert(0.0f <= randomization && randomization <= 1.0f);
    m_scale = scale;
    m_scaleRandomization = randomization;
}

void VoxelParticleSpawnBase::setForce(float force, float randomization) {
    assert(0.0f <= randomization && randomization <= 1.0f);
    m_force = force;
    m_forceRandomization = randomization;
}

void VoxelParticleSpawnBase::setLifetime(float lifetime, float lifetimeRandomization) {
    assert(0.0f <= lifetimeRandomization && lifetimeRandomization <= 1.0f);
    m_lifetime = lifetime;
    m_lifetimeRandomization = lifetimeRandomization;
}

void VoxelParticleSpawnBase::setColor(int color) {
    m_color = color;
}

void VoxelParticleSpawnBase::setEmissiveness(float emissiveness) {
    m_emissiveness = emissiveness;
}

void VoxelParticleSpawnBase::setImpactVector(const glm::vec3& impactVector) {
    m_impactVector = impactVector;
}

glm::vec3 VoxelParticleSpawnBase::createDirectionalSpeed() {
    float speedVal = RandFloat::randomize(m_force, m_forceRandomization) * m_particleBaseForce;
    glm::vec3 speedDir = RandVec3::randUnitVec();

    return speedVal * speedDir + m_impactVector;
}

glm::vec3 VoxelParticleSpawnBase::createAngularSpeed() {
    return RandVec3::randUnitVec() * RandFloat::randomize(m_force, m_forceRandomization) * m_particleAngularBaseForce.get();
}

float VoxelParticleSpawnBase::createLifetime() {
    return RandFloat::randomize(m_lifetime, m_lifetimeRandomization);
}

#include "particlespawnbase.h"

#include <ctime>

#include "world/god.h"
#include "world/world.h"
#include "utils/randvec.h"
#include "utils/randfloat.h"
#include "utils/randbool.h"

#include "particle.h"
#include "particleworld.h"


ParticleSpawnBase::ParticleSpawnBase() :
    m_position(0, 0, 0),
    m_scale(1.0f),
    m_scaleRandomization(0.0f),
    m_force(1.0f),
    m_forceRandomization(0.0f),
    m_lifetime(1.0f),
    m_lifetimeRandomization(0.0f),
    m_color(0xFFFFFF),
    m_colorEmissiveness(0.0f),
    m_impactVector(0, 0, 0),
    m_particleDampening(0.0f),
    m_particleAngularDampening(0.0f),
    m_particleBaseForce(1.0f),
    m_particleAngularBaseForce(1.0f)
{
}

ParticleSpawnBase::~ParticleSpawnBase() {
}

void ParticleSpawnBase::setPosition(const glm::vec3& position) {
    m_position = position;
}

void ParticleSpawnBase::setScale(float scale, float randomization) {
    assert(0.0f <= randomization && randomization <= 1.0f);
    m_scale = scale;
    m_scaleRandomization = randomization;
}

void ParticleSpawnBase::setForce(float force, float randomization) {
    assert(0.0f <= randomization && randomization <= 1.0f);
    m_force = force;
    m_forceRandomization = randomization;
}

void ParticleSpawnBase::setLifetime(float lifetime, float lifetimeRandomization) {
    assert(0.0f <= lifetimeRandomization && lifetimeRandomization <= 1.0f);
    m_lifetime = lifetime;
    m_lifetimeRandomization = lifetimeRandomization;
}

void ParticleSpawnBase::setColor(int color, float emissiveness) {
    m_color = color;
    m_colorEmissiveness = emissiveness;
}
void ParticleSpawnBase::setImpactVector(const glm::vec3& impactVector) {
    m_impactVector = impactVector;
}

glm::vec3 ParticleSpawnBase::createDirectionalSpeed() {
    float speedVal = RandFloat::randomize(m_force, m_forceRandomization) * m_particleBaseForce;
    glm::vec3 speedDir = RandVec3::randUnitVec();

    return speedVal * speedDir + m_impactVector;
}

glm::vec3 ParticleSpawnBase::createAngularSpeed() {
    return RandVec3::randUnitVec() * RandFloat::randomize(m_force, m_forceRandomization) * m_particleAngularBaseForce;
}

float ParticleSpawnBase::createLifetime() {
    return RandFloat::randomize(m_lifetime, m_lifetimeRandomization);
}

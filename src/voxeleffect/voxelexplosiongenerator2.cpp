#include "voxelexplosiongenerator2.h"

#include <ctime>

#include "world/god.h"
#include "world/world.h"
#include "utils/randfloat.h"
#include "utils/randvec.h"

#include "voxelparticle.h"
#include "voxelparticleworld.h"

VoxelExplosionGenerator2::VoxelExplosionGenerator2() :
    m_position(0, 0, 0),
    m_radius(0.5f),
    m_scale(1.0f),
    m_force(1.0f),
    m_forceRandomization(0.0f),
    m_lifetime(1.0f),
    m_lifetimeRandomization(0.0f),
    m_color(0xFFFFFF),
    m_count(10),
    m_impactVector(0, 0, 0),
    m_debrisDampening("physics.debrisDampening"),
    m_debrisAngularDampening("physics.debrisAngularDampening"),
    m_debrisBaseForce("physics.debrisBaseForce"),
    m_debrisAngularBaseForce("physics.debrisAngularBaseForce")
{
}

VoxelExplosionGenerator2::~VoxelExplosionGenerator2() {
}

void VoxelExplosionGenerator2::setPosition(const glm::vec3& position) {
    m_position = position;
}

void VoxelExplosionGenerator2::setRadius(float radius){
    m_radius = radius;
}

void VoxelExplosionGenerator2::setScale(float scale) {
    m_scale = scale;
}

void VoxelExplosionGenerator2::setForce(float force) {
    m_force = force;
}

void VoxelExplosionGenerator2::setLifetime(float lifetime, float lifetimeRandomization){
    assert(0.0f <= lifetimeRandomization && lifetimeRandomization <= 1.0f);
    m_lifetime = lifetime;
    m_lifetimeRandomization = lifetimeRandomization;
}

void VoxelExplosionGenerator2::setColor(int color) {
    m_color = color;
}

void VoxelExplosionGenerator2::setCount(int count) {
    m_count = count;
}

void VoxelExplosionGenerator2::setImpactVector(const glm::vec3& impactVector) {
    m_impactVector = impactVector;
}

void VoxelExplosionGenerator2::spawn() {
    // spawn explosionSpawnCount voxels with color and scale at position within a sphere with radius with a speed of ~force in all directions modified by ~impactVector
    WorldTransform transform;
    transform.setScale(m_scale);

    for (int i = 0; i < m_count; i++){

        glm::vec3 randDirection = createDirectionalSpeed();
        transform.setPosition(m_position + (m_radius * randDirection));

        VoxelParticle* particle = new VoxelParticle(transform, m_color, createLifetime());
        particle->setAngularSpeed(createAngularSpeed(), m_debrisDampening);
        particle->setDirectionalSpeed(randDirection, m_debrisAngularDampening);

        World::instance()->voxelParticleWorld().addParticle(particle);

    }
}


glm::vec3 VoxelExplosionGenerator2::createDirectionalSpeed() {
    float speedVal = RandFloat::randomize(m_force, m_forceRandomization) * m_debrisBaseForce.get();
    glm::vec3 speedDir = RandVec3::randUnitVec();

    return speedVal * speedDir + m_impactVector;
}

glm::vec3 VoxelExplosionGenerator2::createAngularSpeed() {
    return RandVec3::randUnitVec() * RandFloat::randomize(m_force, m_forceRandomization) * m_debrisAngularBaseForce.get();
}

float VoxelExplosionGenerator2::createLifetime() {
    return RandFloat::randomize(m_lifetime, m_lifetimeRandomization);
}
#include "voxelexplosiongenerator.h"

#include <ctime>

#include "world/god.h"
#include "world/world.h"
#include "utils/randvec.h"
#include "utils/randfloat.h"

#include "voxelparticle.h"
#include "voxelparticleworld.h"


VoxelExplosionGenerator::VoxelExplosionGenerator() :
    m_position(0, 0, 0),
    m_orientation(),
    m_scale(1.0f),
    m_force(1.0f),
    m_lifetime(1.0f),
    m_lifetimeRandomization(0.0f),
    m_color(0xFFFFFF),
    m_density(2),
    m_impactVector(0,0,0)
{
}

VoxelExplosionGenerator::~VoxelExplosionGenerator() {
}

void VoxelExplosionGenerator::setPosition(const glm::vec3& position) {
    m_position = position;
}

void VoxelExplosionGenerator::setOrientation(const glm::quat& orientation) {
    m_orientation = orientation;
}

void VoxelExplosionGenerator::setScale(float scale, float randomization) {
    m_scale = scale;
    m_scaleRandomization = randomization;
}

void VoxelExplosionGenerator::setTransform(const WorldTransform& transform) {
    m_position = transform.position();
    m_orientation = transform.orientation();
    m_scale = transform.scale();
}

void VoxelExplosionGenerator::setForce(float force, float randomization) {
    m_force = force;
    m_forceRandomization = randomization;
}

void VoxelExplosionGenerator::setLifetime(float lifetime, float lifetimeRandomization){
    assert(0.0f <= lifetimeRandomization && lifetimeRandomization <= 1.0f);
    m_lifetime = lifetime;
    m_lifetimeRandomization = lifetimeRandomization;
}

void VoxelExplosionGenerator::setColor(int color) {
    m_color = color;
}

void VoxelExplosionGenerator::setDensity(int density) {
    m_density = density;
}

void VoxelExplosionGenerator::setImpactVector(const glm::vec3& impactVector) {
    m_impactVector = impactVector;
}

void VoxelExplosionGenerator::spawn() {
    // spawn explosionSpawnCount voxels with color at position within a cube with edgeLength scale with a speed of ~force in all directions modified by ~impactVector
    WorldTransform transform;
    WorldTransform particleTransform;

    transform.setPosition(m_position);
    transform.setOrientation(m_orientation);

    // center compensates that i,j,k start from 0
    transform.setCenter(glm::vec3(m_density/2));
    transform.setScale(m_scale / m_density);

    particleTransform.setOrientation(m_orientation);

    for (int z = 0; z < m_density; z++) {
        for (int y = 0; y < m_density; y++) {
            for (int x = 0; x < m_density; x++) {

                particleTransform.setScale(createScale());
                particleTransform.setPosition(transform.applyTo(glm::vec3(x, y, z)));

                VoxelParticle* particle = new VoxelParticle(particleTransform, m_color, createLifetime());
                particle->setAngularSpeed(createAngularSpeed(), 0.2);
                particle->setDirectionalSpeed(createDirectionalSpeed(), 0.2);

                World::instance()->voxelParticleWorld().addParticle(particle);

            }
        }
    }
}

glm::vec3 VoxelExplosionGenerator::createDirectionalSpeed() const {
    float speedVal = RandFloat::randomize(m_force, m_forceRandomization);
    glm::vec3 speedDir = RandVec3::randNormalized();

    return speedVal * speedDir + m_impactVector;
}

glm::vec3 VoxelExplosionGenerator::createAngularSpeed() const {
    return RandVec3::rand(-10.0f, 10.0f) * m_force;
}

float VoxelExplosionGenerator::createLifetime() const {
    return RandFloat::randomize(m_lifetime, m_lifetimeRandomization);
}

float VoxelExplosionGenerator::createScale() const {
    return RandFloat::randomize(m_scale / m_density, m_scaleRandomization);
}

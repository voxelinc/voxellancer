#include "voxelexplosiongenerator.h"

#include <ctime>

#include "world/god.h"
#include "world/world.h"
#include "utils/randvec.h"
#include "utils/randfloat.h"
#include "utils/randbool.h"

#include "voxelparticle.h"
#include "voxelparticleworld.h"


VoxelExplosionGenerator::VoxelExplosionGenerator() :
    m_position(0, 0, 0),
    m_orientation(),
    m_scale(1.0f),
    m_scaleRandomization(0.0f),
    m_force(1.0f),
    m_forceRandomization(0.0f),
    m_lifetime(1.0f),
    m_lifetimeRandomization(0.0f),
    m_color(0xFFFFFF),
    m_density(2),
    m_impactVector(0,0,0),
    m_spawnProbability(1.0f),
    m_debrisDampening("physics.debrisDampening"),
    m_debrisAngularDampening("physics.debrisAngularDampening"),
    m_debrisBaseForce("physics.debrisBaseForce"),
    m_debrisAngularBaseForce("physics.debrisAngularBaseForce")
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
    assert(0.0f <= randomization && randomization <= 1.0f);
    m_scale = scale;
    m_scaleRandomization = randomization;
}

void VoxelExplosionGenerator::setTransform(const WorldTransform& transform) {
    m_position = transform.position();
    m_orientation = transform.orientation();
    m_scale = transform.scale();
}

void VoxelExplosionGenerator::setForce(float force, float randomization) {
    assert(0.0f <= randomization && randomization <= 1.0f);
    m_force = force;
    m_forceRandomization = randomization;
}

void VoxelExplosionGenerator::setLifetime(float lifetime, float lifetimeRandomization) {
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

void VoxelExplosionGenerator::setSpawnProbability(float spawnProbability) {
    m_spawnProbability = spawnProbability;
}

void VoxelExplosionGenerator::spawn() {
    WorldTransform gridTransform;
    WorldTransform particleTransform;

    gridTransform.setPosition(m_position);
    gridTransform.setOrientation(m_orientation);
    gridTransform.setCenter(glm::vec3(m_density/2.0f - 0.5f));
    gridTransform.setScale(m_scale / m_density);

    particleTransform.setOrientation(m_orientation);

    for (int z = 0; z < m_density; z++) {
        for (int y = 0; y < m_density; y++) {
            for (int x = 0; x < m_density; x++) {
                if (!RandBool::rand(m_spawnProbability)) {
                    continue;
                }

                particleTransform.setScale(createScale());
                particleTransform.setPosition(gridTransform.applyTo(glm::vec3(x, y, z)));

                VoxelParticle* particle = new VoxelParticle(particleTransform, m_color, createLifetime());
                particle->setAngularSpeed(createAngularSpeed(), m_debrisDampening);
                particle->setDirectionalSpeed(createDirectionalSpeed(), m_debrisAngularDampening);

                World::instance()->voxelParticleWorld().addParticle(particle);
            }
        }
    }
}

glm::vec3 VoxelExplosionGenerator::createDirectionalSpeed() {
    float speedVal = RandFloat::randomize(m_force, m_forceRandomization) * m_debrisBaseForce.get();
    glm::vec3 speedDir = RandVec3::randNormalized();

    return speedVal * speedDir + m_impactVector;
}

glm::vec3 VoxelExplosionGenerator::createAngularSpeed() {
    return RandVec3::rand(-1.0f, 1.0f) * RandFloat::randomize(m_force, m_forceRandomization) * m_debrisAngularBaseForce.get();
}

float VoxelExplosionGenerator::createLifetime() {
    return RandFloat::randomize(m_lifetime, m_lifetimeRandomization);
}

float VoxelExplosionGenerator::createScale() {
    return RandFloat::randomize(m_scale / m_density, m_scaleRandomization);
}


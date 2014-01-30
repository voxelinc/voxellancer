#include "voxelexplosiongenerator.h"

#include <ctime>

#include "world/god.h"
#include "world/world.h"
#include "utils/randfloat.h"
#include "utils/randvec.h"

#include "voxelparticle.h"
#include "voxelparticleworld.h"

VoxelExplosionGenerator::VoxelExplosionGenerator() :
    m_radius(0.5f),
    m_count(10)
{
    m_particleDampening = Property<float>("physics.explosionDampening");
    m_particleAngularDampening = Property<float>("physics.explosionAngularDampening");
    m_particleBaseForce = Property<float>("physics.explosionBaseForce");
    m_particleAngularBaseForce = Property<float>("physics.explosionAngularBaseForce");
}

VoxelExplosionGenerator::~VoxelExplosionGenerator() {
}

void VoxelExplosionGenerator::setRadius(float radius){
    m_radius = radius;
}

void VoxelExplosionGenerator::setCount(int count) {
    m_count = count;
}

void VoxelExplosionGenerator::spawn() {
    // spawn explosionSpawnCount voxels with color and scale at position within a sphere with radius with a speed of ~force in all directions modified by ~impactVector
    Transform transform;
    transform.setScale(m_scale);

    for (int i = 0; i < m_count; i++) {
        glm::vec3 randDirection = createDirectionalSpeed();
        transform.setPosition(m_position + (m_radius * randDirection));

        VoxelParticle* particle = new VoxelParticle(transform, m_color, m_colorEmissiveness, createLifetime());
        particle->setAngularSpeed(createAngularSpeed(), m_particleDampening);
        particle->setDirectionalSpeed(randDirection, m_particleAngularDampening);

        World::instance()->voxelParticleWorld().addParticle(particle);
    }
}

float VoxelExplosionGenerator::createScale() {
    return RandFloat::randomize(m_scale, m_scaleRandomization);
}

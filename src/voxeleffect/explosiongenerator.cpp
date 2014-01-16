#include "explosiongenerator.h"

#include <ctime>

#include "world/god.h"
#include "world/world.h"
#include "utils/randfloat.h"
#include "utils/randvec.h"

#include "particle.h"
#include "particleworld.h"

ExplosionGenerator::ExplosionGenerator() :
    m_radius(0.5f),
    m_count(10)
{
    m_particleDampening = Property<float>("physics.explosionDampening");
    m_particleAngularDampening = Property<float>("physics.explosionAngularDampening");
    m_particleBaseForce = Property<float>("physics.explosionBaseForce");
    m_particleAngularBaseForce = Property<float>("physics.explosionAngularBaseForce");
}

ExplosionGenerator::~ExplosionGenerator() {
}

void ExplosionGenerator::setRadius(float radius) {
    m_radius = radius;
}

void ExplosionGenerator::setCount(int count) {
    m_count = count;
}

void ExplosionGenerator::spawn() {
    // spawn explosionSpawnCount voxels with color and scale at position within a sphere with radius with a speed of ~force in all directions modified by ~impactVector
    WorldTransform transform;
    transform.setScale(m_scale);

    for (int i = 0; i < m_count; i++) {

        glm::vec3 randDirection = createDirectionalSpeed();
        transform.setPosition(m_position + (m_radius * randDirection));

        Particle* particle = new Particle(transform, m_color, m_colorEmissiveness, createLifetime());
        particle->setAngularSpeed(createAngularSpeed(), m_particleDampening);
        particle->setDirectionalSpeed(randDirection, m_particleAngularDampening);

        World::instance()->particleWorld().addParticle(particle);

    }
}

float ExplosionGenerator::createScale() {
    return RandFloat::randomize(m_scale, m_scaleRandomization);
}
#include "voxelexplosiongenerator.h"

#include <ctime>

#include "world/god.h"
#include "world/world.h"
#include "utils/randfloat.h"
#include "utils/randvec.h"

#include "voxelparticledata.h"
#include "voxelparticleworld.h"


VoxelExplosionGenerator::VoxelExplosionGenerator() :
    m_radius(0.5f),
    m_count(10)
{
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

    for (int i = 0; i < m_count; i++) {
        glm::vec3 directionalSpeed = createDirectionalSpeed();

        transform.setScale(createScale());
        transform.setPosition(m_position + (m_radius * glm::normalize(directionalSpeed)));

        Visuals visuals(m_color, m_emissiveness);
        Speed speed(directionalSpeed, createAngularSpeed());

        VoxelParticleSetup particleSetup(
            transform,
            visuals,
            speed,
            createLifetime()
        );

        World::instance()->voxelParticleWorld().addParticle(particleSetup);
    }
}

float VoxelExplosionGenerator::createScale() {
    return RandFloat::randomize(m_scale, m_scaleRandomization);
}

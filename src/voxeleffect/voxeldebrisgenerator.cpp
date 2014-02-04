#include "voxeldebrisgenerator.h"

#include <ctime>

#include "world/god.h"
#include "world/world.h"
#include "utils/randvec.h"
#include "utils/randfloat.h"
#include "utils/randbool.h"

#include "voxelparticle.h"
#include "voxelparticleworld.h"


VoxelDebrisGenerator::VoxelDebrisGenerator() :
    m_orientation(),
    m_density(2),
    m_spawnProbability(1.0f)
{
    m_particleDampening = Property<float>("physics.debrisDirectionalDampening");
    m_particleAngularDampening = Property<float>("physics.debrisAngularDampening");
    m_particleBaseForce = Property<float>("physics.debrisBaseForce");
    m_particleAngularBaseForce = Property<float>("physics.debrisAngularBaseForce");
}

VoxelDebrisGenerator::~VoxelDebrisGenerator() {
}


void VoxelDebrisGenerator::setOrientation(const glm::quat& orientation) {
    m_orientation = orientation;
}

void VoxelDebrisGenerator::setDensity(int density) {
    m_density = density;
}

void VoxelDebrisGenerator::setSpawnProbability(float spawnProbability) {
    m_spawnProbability = spawnProbability;
}

void VoxelDebrisGenerator::spawn() {
    Transform gridTransform;
    Transform particleTransform;

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

                VoxelParticle* particle = new VoxelParticle(particleTransform, m_color, m_emissiveness, createLifetime());
                particle->setAngularSpeed(createAngularSpeed(), m_particleDampening);
                particle->setDirectionalSpeed(createDirectionalSpeed(), m_particleAngularDampening);

                World::instance()->voxelParticleWorld().addParticle(particle);
            }
        }
    }
}

float VoxelDebrisGenerator::createScale() {
    return RandFloat::randomize(m_scale / m_density, m_scaleRandomization);
}


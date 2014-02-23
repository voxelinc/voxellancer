#include "voxeldebrisgenerator.h"

#include <ctime>

#include "geometry/speed.h"
#include "geometry/acceleration.h"

#include "utils/randvec.h"
#include "utils/randfloat.h"
#include "utils/randbool.h"

#include "display/rendering/visuals.h"

#include "voxelparticleengine.h"
#include "voxelparticlesetup.h"

#include "world/world.h"



VoxelDebrisGenerator::VoxelDebrisGenerator() :
    VoxelParticleSpawnBase("physics.debrisDirectionalDampening",
                           "physics.debrisAngularDampening",
                           "physics.debrisBaseForce",
                           "physics.debrisAngularBaseForce"),
    m_orientation(),
    m_density(2),
    m_spawnProbability(1.0f)
{
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

                Visuals visuals(m_color, m_emissiveness);
                Speed speed(createDirectionalSpeed(), createAngularSpeed());

                VoxelParticleSetup particleSetup(
                    particleTransform,
                    visuals,
                    speed,
                    createLifetime()
                );

                World::instance()->voxelParticleEngine().addParticle(particleSetup);
            }
        }
    }
}

float VoxelDebrisGenerator::createScale() {
    return RandFloat::randomize(m_scale / m_density, m_scaleRandomization);
}


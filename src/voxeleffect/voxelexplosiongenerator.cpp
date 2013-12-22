#include "voxelexplosiongenerator.h"

#include <ctime>

#include "world/god.h"
#include "world/world.h"
#include "utils/randfloat.h"
#include "voxelexplosionparticle.h"


VoxelExplosionGenerator::VoxelExplosionGenerator() :
    prop_lifetime("vfx.explosionLifetime"),
    m_position(0, 0, 0),
    m_orientation(),
    m_scale(1.0f),
    m_force(1.0f),
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

void VoxelExplosionGenerator::setScale(float scale) {
    m_scale = scale;
}

void VoxelExplosionGenerator::setTransform(const WorldTransform& transform) {
    m_position = transform.position();
    m_orientation = transform.orientation();
    m_scale = transform.scale();
}

void VoxelExplosionGenerator::setForce(float force) {
    m_force = force;
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
    // Maximum voxel edge length is spawnRadius * 2 / sqrt(2) for 1 voxel
    WorldTransform transform;
    transform.setPosition(m_position);
    transform.setOrientation(m_orientation);
    transform.setCenter(glm::vec3(m_scale / 2.0f));

    float scale = m_scale / m_density;
    for (int i = 0; i < m_density; i++){
        for (int j = 0; j < m_density; j++){
            for (int k = 0; k < m_density; k++){
                VoxelExplosionParticle* newObject = new VoxelExplosionParticle(0.95f * scale, prop_lifetime * m_force); //multiply 0.95 to certainly be below the collision threshold
                Voxel* voxel = new Voxel(glm::ivec3(0, 0, 0), m_color, 0.000001f, 0.1f);
                voxel->addToObject(newObject);
                newObject->setCrucialVoxel(glm::ivec3(0, 0, 0));


                newObject->setPosition( transform.applyTo( scale * (glm::vec3(i, j, k))));
                newObject->setOrientation(m_orientation);


                float angX = RandFloat::rand(-180, 180);
                float angY = glm::degrees(glm::acos(2 * RandFloat::rand(0, 1) - 1));
                glm::vec3 speedVec = glm::quat(glm::vec3(angX, angY, 0.0f)) * glm::vec3(0, 0, RandFloat::rand(1, 10));
                newObject->physics().setSpeed( m_orientation * (m_force * 10.0f * glm::normalize(speedVec)) + m_impactVector);


                newObject->physics().setAngularSpeed(glm::vec3(
                    RandFloat::rand(-10, 10),
                    RandFloat::rand(-10, 10),
                    RandFloat::rand(-10, 10)));

                World::instance()->god().scheduleSpawn(newObject);
            }
        }
    }
}

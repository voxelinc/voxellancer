#include "voxelexplosiongenerator.h"

#include <ctime>



#include "world/god.h"
#include "world/world.h"
#include "utils/randfloat.h"
#include "voxelexplosionparticle.h"

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
    transform.setPosition(m_position);
    transform.setOrientation(m_orientation);
    // center compensates that i,j,k start from 0
    transform.setCenter(m_scale * (glm::vec3(0.5f - (0.5f / m_density))));

    float scale = m_scale / m_density;
    for (int z = 0; z < m_density; z++){
        for (int y = 0; y < m_density; y++){
            for (int x = 0; x < m_density; x++){
                float lifetime = m_lifetime * RandFloat::rand(1.0f - m_lifetimeRandomization, 1.0f + m_lifetimeRandomization);

                //multiply scale with 0.95 to certainly be below the collision threshold
                VoxelExplosionParticle* newObject = new VoxelExplosionParticle(0.95f * scale, lifetime);
                Voxel* voxel = new Voxel(glm::ivec3(0), m_color, 0.000001f, 0.1f);
                voxel->addToObject(newObject);
                newObject->setCrucialVoxel(glm::ivec3(0));

                newObject->setPosition(transform.applyTo(scale * (glm::vec3(x, y, z))));
                newObject->setOrientation(m_orientation);

                float angX = RandFloat::rand(-180.0f, 180.0f);
                float angY = glm::degrees(glm::acos(RandFloat::rand(-1.0f, 1.0f)));
                glm::vec3 speedVec = glm::quat(glm::vec3(angX, angY, 0.0f)) * glm::vec3(0, 0, RandFloat::rand(1.0f, 10.0f));
                newObject->physics().setSpeed(m_orientation * (m_force * speedVec) + m_impactVector);

                newObject->physics().setAngularSpeed(glm::vec3(
                    m_force * RandFloat::rand(-10.0f, 10.0f),
                    m_force * RandFloat::rand(-10.0f, 10.0f),
                    m_force * RandFloat::rand(-10.0f, 10.0f)));


                VoxelParticle* particle = new VoxelParticle(newObject->transform(), m_color, lifetime*0.1f);
                particle->setAngularSpeed(newObject->physics().angularSpeed(), 0.2f);
                particle->setDirectionalSpeed(newObject->physics().speed()*5.0f, 0.2f);

                World::instance()->voxelParticleWorld().addParticle(particle);

                //World::instance()->god().scheduleSpawn(newObject);
            }
        }
    }
}

#include "voxelexplosiongenerator2.h"

#include <ctime>

#include "world/god.h"
#include "world/world.h"
#include "utils/randfloat.h"
#include "voxeleffectparticle.h"


VoxelExplosionGenerator2::VoxelExplosionGenerator2() :
    m_position(0, 0, 0),
    m_radius(1),
    m_scale(1.0f),
    m_force(1.0f),
    m_lifetime(1.0f),
    m_lifetimeRandomization(0.0f),
    m_color(0xFFFFFF),
    m_count(10),
    m_impactVector(0,0,0)
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
    transform.setPosition(m_position);

    for (int i = 0; i < m_count; i++){
        float lifetime = m_lifetime;
        if (m_lifetimeRandomization > 0.0f) lifetime *= RandFloat::rand(1.0f - m_lifetimeRandomization, 1.0f + m_lifetimeRandomization);

        VoxelEffectParticle* newObject = new VoxelEffectParticle(0.95f * m_scale, lifetime);
        Voxel* voxel = new Voxel(glm::ivec3(0), m_color, 0.00000001f, 0.01f);
        voxel->addToObject(newObject);
        newObject->setCrucialVoxel(glm::ivec3(0));

        float angX = RandFloat::rand(-180.0f, 180.0f);
        float angY = glm::degrees(glm::acos(RandFloat::rand(-1.0f, 1.0f)));
        glm::vec3 randDirection = glm::quat(glm::vec3(angX, angY, 0.0f)) * glm::vec3(0, 0, RandFloat::rand(0.0f, 1.0f));

        newObject->setPosition(transform.applyTo(m_scale * randDirection));
        newObject->physics().setSpeed((m_force * randDirection) + m_impactVector);

        newObject->physics().setAngularSpeed(glm::vec3(
            m_force * RandFloat::rand(-10.0f, 10.0f),
            m_force * RandFloat::rand(-10.0f, 10.0f),
            m_force * RandFloat::rand(-10.0f, 10.0f)));

        World::instance()->god().scheduleSpawn(newObject);

    }
}
#include "ringexplosion.h"

#include <glm/gtc/quaternion.hpp>

#include "display/rendering/visuals.h"

#include "geometry/speed.h"
#include "geometry/transform.h"

#include "utils/randfloatpool.h"
#include "utils/randvec3pool.h"

#include "voxeleffect/voxelexplosiongenerator.h"
#include "voxeleffect/voxelparticleengine.h"
#include "voxeleffect/voxelparticlesetup.h"

#include "world/world.h"


RingExplosion::RingExplosion() {

}

RingExplosion::~RingExplosion() = default;

void RingExplosion::spawn(const glm::vec3& position) {
    m_planeOrientation = glm::quat(glm::vec3(RandFloatPool::rand(0, glm::pi<float>() * 4), RandFloatPool::rand(0, glm::pi<float>() * 4), RandFloatPool::rand(0, glm::pi<float>() * 4)));

    inner(position);
    outer(position);
    fire(position);
}

void RingExplosion::inner(const glm::vec3& position) {
    int count = 320;
    uint32_t color = 0x88AAFF;
    float openingAngle = glm::radians(0.0f);
    float force = 600.0f;
    float forceRandomization = 0.08f;
    float lifetime = 0.4f;
    float lifetimeRandomization = 0.8f;
    float scale = 0.30f;
    float scaleRandomization = 0.4f;

    Transform transform;

    for (int i = 0; i < count; i++) {
        float xAngle = RandFloatPool::rand(-openingAngle, openingAngle);
        float yAngle = RandFloatPool::rand(0.0f, glm::pi<float>() * 4);

        glm::quat localDir(glm::vec3(xAngle, yAngle, 0.0f));
        glm::quat worldDir(m_planeOrientation * localDir);

        Speed speed(worldDir * glm::vec3(1.0f, 0.0f, 0.0f) * RandFloatPool::randomize(force, forceRandomization), RandVec3Pool::randUnitVec());

        transform.setScale(RandFloatPool::randomize(scale, scaleRandomization));
        transform.setPosition(position);

        Visuals visuals(color, 0.8f);

        VoxelParticleSetup particleSetup(
            transform,
            visuals,
            speed,
            RandFloatPool::randomize(lifetime, lifetimeRandomization)
        );

        World::instance()->particleEngine().addParticle(particleSetup, nullptr);
    }
}

void RingExplosion::outer(const glm::vec3& position) {
    int count = 320;
    uint32_t color = 0xFF5500;
    float openingAngle = glm::radians(0.0f);
    float force = 1000.0f;
    float forceRandomization = 0.02f;
    float lifetime = 0.4f;
    float lifetimeRandomization = 0.8f;
    float scale = 0.50f;
    float scaleRandomization = 0.4f;

    Transform transform;

    for (int i = 0; i < count; i++) {
        float xAngle = RandFloatPool::rand(-openingAngle, openingAngle);
        float yAngle = RandFloatPool::rand(0.0f, glm::pi<float>() * 4);

        glm::quat localDir(glm::vec3(xAngle, yAngle, 0.0f));
        glm::quat worldDir(m_planeOrientation * localDir);

        Speed speed(worldDir * glm::vec3(1.0f, 0.0f, 0.0f) * RandFloatPool::randomize(force, forceRandomization), RandVec3Pool::randUnitVec());

        transform.setScale(RandFloatPool::randomize(scale, scaleRandomization));
        transform.setPosition(position);

        Visuals visuals(color, 0.8f);

        VoxelParticleSetup particleSetup(
            transform,
            visuals,
            speed,
            RandFloatPool::randomize(lifetime, lifetimeRandomization)
        );

        World::instance()->particleEngine().addParticle(particleSetup, nullptr);
    }
}

void RingExplosion::fire(const glm::vec3& position) {
    VoxelExplosionGenerator generator(nullptr);
    generator.setPosition(position);
    generator.setRadius(1.0f);
    generator.setScale(1.0f / 1.5f, 0.5f);
    generator.setCount(30);
    generator.setEmissiveness(1.2f);
    generator.setColor(0xFF0000);
    generator.setForce(3.0f, 0.6f);
    generator.setLifetime(1.0f, 1.0f);
    generator.spawn();

    generator.setScale(1.0f / 3.0f, 0.5f);
    generator.setCount(10);
    generator.setEmissiveness(0.8f);
    generator.setColor(0xFF9900);
    generator.setForce(12.0f, 0.4f);
    generator.setLifetime(1.4f, 0.7f);
    generator.spawn();

    generator.setScale(2.0f * 1.3f);
    generator.setCount(6);
    generator.setEmissiveness(1.8f);
    generator.setColor(0xFF3300);
    generator.setForce(100.0f, 0.4f);
    generator.setLifetime(2.4f, 0.7f);
    generator.spawn();
}


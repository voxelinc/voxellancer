#include "ringexplosion.h"

#include <glm/gtc/quaternion.hpp>

#include "display/rendering/visuals.h"

#include "geometry/speed.h"
#include "geometry/transform.h"

#include "utils/randfloatpool.h"
#include "utils/randvec3pool.h"

#include "voxeleffect/voxelparticleengine.h"
#include "voxeleffect/voxelparticlesetup.h"

#include "world/world.h"


RingExplosion::RingExplosion() {

}

RingExplosion::~RingExplosion() = default;

void RingExplosion::spawn(const glm::vec3& position) {
    glm::quat planeOrientation(glm::vec3(RandFloatPool::rand(0, glm::pi<float>() * 4), RandFloatPool::rand(0, glm::pi<float>() * 4), RandFloatPool::rand(0, glm::pi<float>() * 4)));
    int count = 120;
    uint32_t color = 0xFF2200;
    float openingAngle = glm::radians(3.0f);
    float force = 70.0f;
    float forceRandomization = 0.05f;
    float lifetime = 1.5f;
    float lifetimeRandomization = 1.0f;
    float scale = 0.30f;
    float scaleRandomization = 0.4f;

    Transform transform;

    for (int i = 0; i < count; i++) {
        float xAngle = RandFloatPool::rand(-openingAngle, openingAngle);
        float yAngle = RandFloatPool::rand(0.0f, glm::pi<float>() * 4);

        glm::quat localDir(glm::vec3(xAngle, yAngle, 0.0f));
        glm::quat worldDir(planeOrientation * localDir);

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


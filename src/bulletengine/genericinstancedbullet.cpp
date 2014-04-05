#include "genericinstancedbullet.h"

#include "voxeleffect/voxelexplosiongenerator.h"


GenericInstancedBullet::GenericInstancedBullet()
{
}

const SoundProperties& GenericInstancedBullet::hitSound() const {
    return m_hitSound;
}

void GenericInstancedBullet::setHitSound(const SoundProperties& hitSound) {
    m_hitSound = hitSound;
}

void GenericInstancedBullet::spawnExplosion() {
/*    VoxelExplosionGenerator generator(this);

    generator.setPosition(transform().position());
    generator.setRadius(transform().scale());
    generator.setScale(transform().scale() / 2.0f);
    generator.setCount(16);
    generator.setEmissiveness(0.4f);
    generator.setColor(0xFF0000);
    generator.setForce(0.6f);
    generator.setLifetime(0.7f, 0.2f);

    generator.spawn();
*/
}


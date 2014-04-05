#include "genericworldobjectbullet.h"

#include "voxeleffect/voxelexplosiongenerator.h"


GenericWorldObjectBullet::GenericWorldObjectBullet():
    m_emissiveness(0.0f)
{
}

float GenericWorldObjectBullet::emissiveness() const {
    return m_emissiveness;
}

void GenericWorldObjectBullet::setEmissiveness(float emissiveness) {
    m_emissiveness = emissiveness;
}

const SoundProperties& GenericWorldObjectBullet::hitSound() const {
    return m_hitSound;
}

void GenericWorldObjectBullet::setHitSound(const SoundProperties& hitSound) {
    m_hitSound = hitSound;
}

void GenericWorldObjectBullet::spawnExplosion() {
    VoxelExplosionGenerator generator(this);

    generator.setPosition(m_transform.position());
    generator.setRadius(m_transform.scale());
    generator.setScale(m_transform.scale() / 2.0f);
    generator.setCount(16);
    generator.setEmissiveness(0.4f);
    generator.setColor(0xFF0000);
    generator.setForce(0.6f);
    generator.setLifetime(0.7f, 0.2f);

    generator.spawn();
}


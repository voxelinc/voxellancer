#include "gunbullet.h"

#include "sound/sound.h"
#include "sound/soundmanager.h"

#include "voxeleffect/voxelexplosiongenerator.h"


GunBullet::GunBullet(WorldObject* creator, float lifetime) :
    Bullet(creator, lifetime, 0.5f)
{
    m_objectInfo.setName("GunBullet");
}

void GunBullet::onCollision() {
    Bullet::onCollision();
    SoundManager::current()->play("data/sound/hit2.ogg", m_transform.position());
}

float GunBullet::emissiveness() {
    return 0.4f;
}

void GunBullet::spawnExplosion() {
    VoxelExplosionGenerator generator;

    generator.setPosition(m_transform.position());
    generator.setRadius(m_transform.scale());
    generator.setScale(m_transform.scale() / 2.0f);
    generator.setCount(16);
    generator.setColor(0xFF0000, emissiveness());
    generator.setForce(0.6f);
    generator.setLifetime(0.7f, 0.2f);

    generator.spawn();
}



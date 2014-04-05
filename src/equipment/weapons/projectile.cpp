#include "projectile.h"

#include "world/god.h"
#include "world/world.h"
#include "sound/soundmanager.h"


Projectile::Projectile():
    m_creator(nullptr),
    m_lifetime(0.0f)
{
}

WorldObject* Projectile::creator() {
    return m_creator;
}

void Projectile::setCreator(WorldObject* creator) {
    m_creator = creator;
}

float Projectile::lifetime() const {
    return m_lifetime;
}

void Projectile::setLifetime(float lifetime) {
    m_lifetime = lifetime;
}

void Projectile::update(float deltaSec) {
    m_lifetime -= deltaSec;

    if (m_lifetime <= 0.0f) {
        onLifetimeOver();
        remove();
    }
}

void Projectile::onLifetimeOver() {

}

void Projectile::onCollision() {
    SoundManager::current()->play(hitSound(), transform().position());

    spawnExplosion();
    remove();
}

void Projectile::onSpawnFail() {
    spawnExplosion();
}


#pragma once

#include "geometry/speed.h"

#include "sound/soundproperties.h"


class SoundProperties;
class WorldObject;

/**
 *   Base class for everything shot by a weapon, characterised by
 *       - doesn't collide with its creator
 *       - destroyed after lifetime is over
*/
class Projectile {
public:
    Projectile();

    virtual Transform& transform() = 0;
    virtual void setTransform(const Transform& transform) = 0;

    virtual void setSpeed(const Speed& speed) = 0;

    WorldObject* creator();
    virtual void setCreator(WorldObject* creator);

    float lifetime() const;
    void setLifetime(float lifetime);

    const SoundProperties& hitSound() const;
    void setHitSound(const SoundProperties& hitSound);

    virtual void update(float deltaSec);

    virtual void spawn() = 0;
    virtual void remove() = 0;

    virtual void onCollision();
    virtual void onSpawnFail();

protected:
    WorldObject* m_creator;
    float m_lifetime;
    SoundProperties m_hitSound;

    virtual void onLifetimeOver();
    virtual void spawnExplosion() = 0;
};


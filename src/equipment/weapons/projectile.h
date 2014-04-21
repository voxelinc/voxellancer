#pragma once

#include "sound/soundproperties.h"

#include "worldobject/worldobject.h"


class SoundProperties;

/**
 * Base class for everything shot by a weapon, characterised by
 *  - doesn't collide with creator
 *  - destroyed after lifetime is over
 */
class Projectile: public WorldObject {
public:
    Projectile();

    WorldObject* creator();
    void setCreator(WorldObject* creator);

    float lifetime() const;
    void setLifetime(float lifetime);

    const SoundProperties& hitSound() const;
    void setHitSound(const SoundProperties& hitSound);

    virtual void update(float deltaSec) override;

    virtual void onCollision() override;
    virtual void onSpawnFail() override;


protected:
    WorldObject* m_creator;
    float m_lifetime;
    SoundProperties m_hitSound;
    float m_emissiveness;

    virtual void onLifetimeOver();
    virtual void spawnExplosion() = 0;
};


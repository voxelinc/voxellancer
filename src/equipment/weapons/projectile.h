#pragma once

#include <memory>

#include "sound/soundproperties.h"

#include "worldobject/worldobject.h"


class Explosion;
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

    Explosion* explosion();
    void setExplosion(const std::shared_ptr<Explosion>& explosion);

    virtual void update(float deltaSec) override;

    virtual void onCollision() override;
    virtual void onSpawnFail() override;


protected:
    WorldObject* m_creator;
    float m_lifetime;
    SoundProperties m_hitSound;
    float m_emissiveness;
    std::shared_ptr<Explosion> m_explosion;

    virtual void onLifetimeOver();
};


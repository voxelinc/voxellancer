#pragma once

#include "geometry/speed.h"

#include "worldobject/worldobject.h"


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

    virtual const SoundProperties& hitSound() const = 0;

    virtual Transform& transform() = 0;
    virtual void setTransform(const Transform& transform) = 0;

    virtual void setSpeed(const Speed& speed) = 0;

    WorldObject* creator();
    virtual void setCreator(WorldObject* creator);

    float lifetime() const;
    void setLifetime(float lifetime);

    virtual void update(float deltaSec);

    virtual void remove() = 0;

    void onCollision();
    void onSpawnFail();


protected:
    WorldObject* m_creator;
    float m_lifetime;

    virtual void onLifetimeOver();
    virtual void spawnExplosion() = 0;
};


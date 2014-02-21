#pragma once

#include "projectile.h"


class SoundProps;

/*
    Base class for every Projectile that flies with a constant undamped speed
    on a target and is destroyed on collision. Also, not displayed on HUD
*/
class Bullet: public Projectile {
public:
    Bullet();

    virtual const SoundProps& hitSound() const = 0;

    virtual void update(float deltaSec) override;

    virtual void onCollision() override;
    virtual void onSpawnFail() override;


protected:
    virtual void spawnExplosion() = 0;
};


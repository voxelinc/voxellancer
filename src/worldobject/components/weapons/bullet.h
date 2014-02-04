#pragma once

#include "projectile.h"


/*
    Base class for every Projectile that flies with a constant undamped speed
    on a target and is destroyed on collision. Also, not displayed on HUD
*/
class Bullet: public Projectile {
public:
    Bullet();

    virtual void update(float deltaSec) override;

    virtual void onCollision() override;
    virtual void onSpawnFail() override;


protected:
    virtual void spawnExplosion() = 0;
};


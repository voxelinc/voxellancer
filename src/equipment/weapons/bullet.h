#pragma once

#include "projectile.h"


class SoundProperties;

/**
 * Base class for every Projectile that flies with a constant undamped speed
 * and is destroyed on collision. Also, not displayed on HUD.
 */
class Bullet: public Projectile {
public:
    Bullet();

    virtual WorldObjectType objectType() const override;

    virtual void update(float deltaSec) override;

    virtual bool passiveForCollisionDetection();


protected:
    void spawnExplosion() override;
};


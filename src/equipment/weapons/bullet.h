#pragma once

#include "geometry/transform.h"

#include "projectile.h"


class SoundProperties;

/**
 *   Base class for every Projectile that flies with a constant undamped speed
 *   on a target and is destroyed on collision. Also, not displayed on HUD
 */
class Bullet: public Projectile {
public:
    Bullet();

    virtual void update(float deltaSec) override;

    virtual float length() = 0;


protected:

};


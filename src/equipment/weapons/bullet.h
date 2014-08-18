#pragma once

#include "geometry/transform.h"

#include "projectile.h"


class SoundProperties;

/**
 * Base class for every Projectile that flies with a constant undamped speed
 * and is destroyed on collision. Also, not displayed on HUD.
 */
class Bullet: public Projectile {
public:
    Bullet();

    virtual glm::vec3 extent() = 0;
};


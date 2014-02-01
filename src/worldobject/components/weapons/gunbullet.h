#pragma once

#include "bullet.h"


class GunBullet: public Bullet {

public:
    Bullet(WorldObject* creator, float lifetime);

    virtual void onCollision() override;
    virtual float emissiveness() override;


protected:
    virtual void spawnExplosion() override;
};


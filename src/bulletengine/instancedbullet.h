#pragma once

#include "equipment/weapons/bullet.h"


class InstancedBullet : public Bullet {
public:
    InstancedBullet();

    virtual void update(float deltaSec) override;

    virtual void spawn() override;
    virtual float length() override;
};


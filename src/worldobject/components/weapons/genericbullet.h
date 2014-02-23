#pragma once

#include <string>

#include "bullet.h"



class GenericBullet: public Bullet {
public:
    GenericBullet();

    virtual float emissiveness() const override;
    void setEmissiveness(float emissiveness);


protected:
    float m_emissiveness;

    virtual void spawnExplosion() override;
};


#pragma once

#include <string>

#include "bullet.h"

#include "sound/soundproperties.h"



class GenericBullet: public Bullet {
public:
    GenericBullet();

    virtual float emissiveness() const override;
    void setEmissiveness(float emissiveness);


protected:
    float m_emissiveness;
    SoundProperties m_hitSound;
    virtual void spawnExplosion() override;
};


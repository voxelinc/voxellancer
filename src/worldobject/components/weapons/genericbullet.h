#pragma once

#include <string>

#include "bullet.h"

#include "sound/soundprops.h"



class GenericBullet: public Bullet {
public:
    GenericBullet();

    virtual float emissiveness() const override;
    void setEmissiveness(float emissiveness);

    virtual const SoundProps& hitSound() const override;
    void setHitSound(const SoundProps& hitSound);
    

protected:
    float m_emissiveness;
    SoundProps m_hitSound;
    virtual void spawnExplosion() override;
};


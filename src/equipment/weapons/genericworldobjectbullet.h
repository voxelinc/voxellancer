#pragma once

#include "sound/soundproperties.h"

#include "equipment/weapons/worldobjectbullet.h"



class GenericWorldObjectBullet: public WorldObjectBullet {
public:
    GenericWorldObjectBullet();

    virtual float emissiveness() const override;
    void setEmissiveness(float emissiveness);

    virtual const SoundProperties& hitSound() const override;
    void setHitSound(const SoundProperties& hitSound);


protected:
    float m_emissiveness;
    SoundProperties m_hitSound;

    virtual void spawnExplosion() override;
};

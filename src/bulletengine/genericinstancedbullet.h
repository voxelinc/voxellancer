#pragma once

#include "sound/soundproperties.h"

#include "instancedbullet.h"


class GenericInstancedBullet : public InstancedBullet {
public:
    GenericInstancedBullet();

    virtual const SoundProperties& hitSound() const override;
    void setHitSound(const SoundProperties& hitSound);


protected:
    SoundProperties m_hitSound;

    virtual void spawnExplosion() override;
};


#pragma once



#include "sound/soundproperties.h"

#include "instancedbullet.h"


class GenericInstancedBullet : public InstancedBullet {
public:
    GenericInstancedBullet(const Handle<InstancedBulletContainer>& prototype, const std::string& name);

    virtual const SoundProperties& hitSound() const override;
    void setHitSound(const SoundProperties& hitSound);


protected:
    SoundProperties m_hitSound;

    virtual void spawnExplosion() override;
};


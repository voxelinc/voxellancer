#pragma once

#include "sound/soundproperties.h"

#include "instancedbullet.h"


class GenericInstancedBullet : public InstancedBullet {
public:
    GenericInstancedBullet(const Handle<InstancedBulletContainer>& prototype, const std::string& name);


protected:
    float m_emissiveness;
    SoundProperties m_hitSound;

    virtual void spawnExplosion() override;
};


#pragma once

#include "worldobject/components/weapons/rocket.h"

#include "worldobject/handle/handle.h"


class Sound;

class Torpedo: public Rocket {

public:
    Torpedo(float lifetime, WorldObject* target);

    virtual void update(float deltaSec);

    virtual void onCollision() override;


private:
    std::shared_ptr<Sound> m_sound;

    virtual void spawnExplosion() override;
};


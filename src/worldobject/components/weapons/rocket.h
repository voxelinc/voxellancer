#pragma once

#include <memory>

#include "ai/aitask.h"
#include "ai/boardcomputer.h"

#include "worldobject/worldobject.h"
#include "worldobject/handle/handle.h"

#include "projectile.h"
#include "sound/soundprops.h"


class Sound;

/*
    Base class for Projectiles that follow a target and attempt to crush into it.
    Also, currently explodes on any collision
*/
class Rocket: public Projectile {
public:
    Rocket();

    WorldObject* target();
    void setTarget(WorldObject* targetObject);
    
    void setSound(std::shared_ptr<Sound> sound);
    
    const SoundProps& explosionSound();
    void setExplosionSound(const SoundProps& soundProps);

    virtual void update(float deltaSec) override;

    virtual void onCollision() override;
    virtual void onSpawnFail() override;


protected:
    Handle<WorldObject> m_targetHandle;
    BoardComputer m_boardComputer;
    std::unique_ptr<AiTask> m_aiTask;
    std::shared_ptr<Sound> m_sound;
    SoundProps m_explosionSound;

    virtual void spawnExplosion() = 0;
};


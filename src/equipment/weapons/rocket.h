#pragma once

#include <memory>

#include "ai/aitask.h"
#include "ai/boardcomputer.h"

#include "utils/handle/handle.h"

#include "worldobject/worldobject.h"

#include "projectile.h"



/*
    Base class for Projectiles that follow a target and attempt to crush into it.
    Also, currently explodes on any collision
*/
class Rocket: public Projectile {
public:
    Rocket();

    WorldObject* target();
    void setTarget(WorldObject* targetObject);

    virtual void update(float deltaSec) override;

    virtual void onCollision() override;
    virtual void onSpawnFail() override;


protected:
    Handle<WorldObject> m_targetHandle;
    BoardComputer m_boardComputer;
    std::unique_ptr<AiTask> m_aiTask;

    virtual void spawnExplosion() = 0;
};


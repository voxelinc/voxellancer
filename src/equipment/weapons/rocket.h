#pragma once

#include <memory>

#include "ai/aitask.h"
#include "ai/boardcomputer.h"

#include "utils/handle/handle.h"

#include "worldobject/worldobject.h"

#include "projectile.h"
#include "sound/soundproperties.h"


class Sound;

/**
 *   Base class for Projectiles that follow a target and attempt to crush into it.
 *   Also, currently explodes on any collision
*/
class Rocket: public Projectile, public WorldObject {
public:
    Rocket();

    virtual WorldObjectType objectType() const override;

    virtual Transform& transform() override;
    virtual void setTransform(const Transform& transform) override;

    virtual void setSpeed(const Speed& speed) override;

    virtual void setCreator(WorldObject* creator) override;

    WorldObject* target();
    virtual void setTarget(WorldObject* targetObject);

    virtual void update(float deltaSec) override;

    virtual void spawn() override;
    virtual void remove() override;

    virtual void onCollision() override;
    virtual void onSpawnFail() override;


protected:
    Handle<WorldObject> m_targetHandle;
    BoardComputer m_boardComputer;
    std::unique_ptr<AiTask> m_aiTask;

    void spawnExplosion() override;
    void onLifetimeOver() override;
};


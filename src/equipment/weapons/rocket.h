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
class Rocket: public Projectile {
public:
    Rocket();

    virtual WorldObjectType objectType() const override;

    WorldObject* target();
    void setTarget(WorldObject* targetObject);

    virtual void update(float deltaSec) override;


protected:
    Handle<WorldObject> m_targetHandle;
    BoardComputer m_boardComputer;
    std::unique_ptr<AiTask> m_aiTask;

};


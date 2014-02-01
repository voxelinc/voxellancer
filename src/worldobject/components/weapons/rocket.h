#pragma once

#include "worldobject/worldobject.h"
#include "worldobject/handle/handle.h"


class Rocket: public WorldObject {
public:
    Rocket(float lifetime, WorldObject* targetObject, float scale);

    WorldObject* targetObject();

    virtual void update(float deltaSec) override;

    virtual void onCollision() override;
    virtual void onSpawnFail() override;


protected:
    float m_lifetime;
    Handle<WorldObject> m_targetHandle;

    virtual void spawnExplosion();
};


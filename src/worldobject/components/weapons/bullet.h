#pragma once

#include "worldobject/worldobject.h"


class Bullet: public WorldObject {
public:
    Bullet(WorldObject* creator, float lifetime, float scale);

    WorldObject* creator() const;

    virtual bool specialIsCollideableWith(const CollisionFilterable* other) const override;

    virtual void onCollision() override;
    virtual void onSpawnFail() override;

    virtual void update(float deltaSec) override;


protected:
    WorldObject *m_creator;
    float m_lifetime;


    virtual void spawnExplosion();
};


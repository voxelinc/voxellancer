#pragma once

#include "worldobject/worldobject.h"
#include "resource/clustercache.h"


class Bullet : public WorldObject {

public:
    Bullet(WorldObject* creator, float lifetime);

    WorldObject* creator() const;

    virtual bool specialIsCollideableWith(const CollisionFilterable* other) const override;

    virtual void update(float deltaSec) override;

    virtual void onCollision() override;
    virtual void onSpawnFail() override;

    virtual float emissiveness() override;

protected:
    void spawnExplosion();

    WorldObject *m_creator;
	float m_lifetime;

	void explode();
};


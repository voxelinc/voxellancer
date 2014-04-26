#pragma once

#include "worldobject/worldobject.h"

#include "bullet.h"


class WorldObjectBullet : public Bullet, public WorldObject {
public:
    WorldObjectBullet();

    virtual Transform& transform() override;
    virtual void setTransform(const Transform& transform) override;

    virtual void setSpeed(const Speed& speed) override;

    virtual void setCreator(WorldObject* creator) override;

    virtual WorldObjectType objectType() const override;

    virtual void remove() override;

    virtual void update(float deltaSec);

    virtual void spawn() override;
    virtual float length() override;

    virtual bool passiveForCollisionDetection() override;


protected:
    void spawnExplosion() override;
};


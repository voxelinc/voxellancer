#pragma once

#include "worldobject/worldobject.h"


/*
    Base class for everything shot by a weapon, characterised by
        - doesn't collide with creator
        - destroyed after lifetime is over
*/
class Projectile: public WorldObject {
public:
    Projectile();

    WorldObject* creator();
    void setCreator(WorldObject* creator);

    float lifetime() const;
    void setLifetime(float lifetime);

    virtual void update(float deltaSec) override;


protected:
    WorldObject* m_creator;
    float m_lifetime;

    virtual void onLifetimeOver();
};


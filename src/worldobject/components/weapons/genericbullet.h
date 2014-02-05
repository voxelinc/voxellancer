#pragma once

#include <string>

#include "utils/genericentity.h"

#include "worldobject/genericworldobject.h"

#include "bullet.h"



class GenericBullet: public GenericWorldObject, public Bullet {
public:
    GenericBullet(const std::string& propertyPrefix);

    virtual float emissiveness() const override;


protected:
    Property<float> m_emissiveness;

    virtual void spawnExplosion() override;
};


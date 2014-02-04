#pragma once

#include <string>

#include "utils/genericentity.h"

#include "worldobject/genericworldobject.h"

#include "bullet.h"



class GenericBullet: public GenericWorldObject, public Bullet {
public:
    GenericBullet(const std::string& propertyPrefix);


protected:
    virtual void spawnExplosion() override;
};


#pragma once

#include <string>

#include "worldobject/genericship.h"
#include "worldobject/genericworldobject.h"
#include "worldobject/components/weapons/genericbullet.h"
#include "worldobject/components/weapons/genericrocket.h"

class Ship;
class WorldObject;

/*
    To generate worldobjects by name, load their settings
    and equip them with engines and weapons
*/
class WorldObjectFactory {
public:
    WorldObjectFactory();

    void equipSomehow(WorldObject* worldObject);
};


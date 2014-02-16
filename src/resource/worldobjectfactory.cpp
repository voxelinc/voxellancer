#include "worldobjectfactory.h"

#include <list>

#include "worldobject/components/hardpoint.h"
#include "worldobject/components/engineslot.h"
#include "worldobject/components/weapons/bullet.h"
#include "worldobject/components/weapons/rocket.h"
#include "worldobject/ship.h"
#include "worldobject/worldobject.h"

#include "clustercache.h"
#include "enginebuilder.h"
#include "weaponbuilder.h"
#include "worldobjectfactory.h"


WorldObjectFactory::WorldObjectFactory() {

}

void WorldObjectFactory::equipSomehow(WorldObject* worldObject) {
    for(Hardpoint* hardpoint : worldObject->components().hardpoints()) {
        if(!hardpoint->mountables().empty()) {
            Weapon* weapon = WeaponBuilder(hardpoint->mountables().front()).build();
            hardpoint->setWeapon(weapon);
        }
    }
    for(EngineSlot* engineSlot : worldObject->components().engineSlots()) {
        if(!engineSlot->mountables().empty()) {
            Engine* engine = EngineBuilder(engineSlot->mountables().front()).build();
            engineSlot->setEngine(engine);
        }
    }
}


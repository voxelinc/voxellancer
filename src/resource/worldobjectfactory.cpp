#include "worldobjectfactory.h"

#include <list>

#include "worldobject/components/hardpoint.h"
#include "worldobject/components/engineslot.h"
#include "worldobject/ship.h"
#include "worldobject/worldobject.h"

#include "clustercache.h"
#include "worldobjectequipmentfactory.h"


WorldObjectFactory::WorldObjectFactory() {

}

void WorldObjectFactory::equipSomehow(WorldObject* worldObject) {
    for(Hardpoint* hardpoint : worldObject->components().hardpoints()) {
        if(!hardpoint->mountables().empty()) {
            Weapon* weapon = WorldObjectEquipmentFactory().weapon(hardpoint->mountables().front());
            hardpoint->setWeapon(weapon);
        }
    }
    for(EngineSlot* engineSlot : worldObject->components().engineSlots()) {
        if(!engineSlot->mountables().empty()) {
            Engine* engine = WorldObjectEquipmentFactory().engine(engineSlot->mountables().front());
            engineSlot->setEngine(engine);
        }
    }
}


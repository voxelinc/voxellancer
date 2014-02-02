#include "worldobjectequipmentfactory.h"

#include "worldobject/components/engines/enginemk1.h"
#include "worldobject/components/engines/piratethruster.h"
#include "worldobject/components/weapons/gun.h"
#include "worldobject/components/weapons/torpedolauncher.h"


WorldObjectEquipmentFactory::WorldObjectEquipmentFactory() {
    load("engines", "enginemk1");
    load("engines", "piratethruster");
    load("weapons", "gun");
    load("weapons", "torpedolauncher");
}

Weapon* WorldObjectEquipmentFactory::weapon(const std::string& name) {
    if (name == "gun") {
        return new Gun();
    }
    if (name == "torpedolauncher") {
        return new TorpedoLauncher();
    }
}

Engine* WorldObjectEquipmentFactory::engine(const std::string& name) {
    if (name == "piratethruster") {
        return new PirateThruster();
    }
    if (name == "enginemk1") {
        return new EngineMK1();
    }
}

void WorldObjectEquipmentFactory::load(const std::string& category, const std::string& name) {
    PropertyManager::instance()->load(std::string("data/equipment/") + category + "/" + name + ".ini", name);
}


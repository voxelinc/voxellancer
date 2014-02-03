#include "worldobjectequipmentfactory.h"

#include <glow/logging.h>

#include "worldobject/components/engines/enginemk1.h"
#include "worldobject/components/engines/piratethruster.h"
#include "worldobject/components/weapons/gun.h"
#include "worldobject/components/weapons/torpedolauncher.h"


WorldObjectEquipmentFactory::WorldObjectEquipmentFactory() {

}

Weapon* WorldObjectEquipmentFactory::weapon(const std::string& name) {
    if (name == "gun") {
        return new Gun();
    }
    if (name == "torpedolauncher") {
        return new TorpedoLauncher();
    }
    glow::info("No such weapon '%;'", name);
    exit(-1);
}

Engine* WorldObjectEquipmentFactory::engine(const std::string& name) {
    if (name == "piratethruster") {
        return new PirateThruster();
    }
    if (name == "enginemk1") {
        return new EngineMK1();
    }
    glow::info("No such engine '%;'", name);
    exit(-1);
}


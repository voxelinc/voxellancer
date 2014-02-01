#include "worldobjectcomponentfactory.h"

#include "worldobject/components/engines/enginemk1.h"
#include "worldobject/components/engines/piratethruster.h"
#include "worldobject/components/weapons/gun.h"
#include "worldobject/components/weapons/torpedolauncher.h"


WorldObjectComponentFactory::WorldObjectComponentFactory() {
    load("engines", "enginemk1");
    load("engine", "piratethruster");
    load("weapons", "gun");
    load("weapons", "torpedolauncher");
}

Weapon* WorldObjectComponentFactory::weapon(const std::string& name) {
    if (name == "gun") {
        return new Gun();
    }
    if (name == "torpedolauncher") {
        return new TorpedoLauncher();
    }
}

Engine* WorldObjectComponentFactory::engine(const std::string& name) {
    if (name == "piratethruster") {
        return new PirateThruster();
    }
    if (name == "enginemk1") {
        return new EngineMK1();
    }
}

void WorldObjectComponentFactory::load(const std::string& category, const std::string& name) {
    PropertyManager::instance()->load(std::string("data/components/") + category + "/" + name + ".ini", name);
}


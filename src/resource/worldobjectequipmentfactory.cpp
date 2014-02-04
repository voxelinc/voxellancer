#include "worldobjectequipmentfactory.h"

#include <glow/logging.h>

#include "worldobject/components/engines/genericengine.h"
#include "worldobject/components/weapons/genericgun.h"
#include "worldobject/components/weapons/genericrocketlauncher.h"


WorldObjectEquipmentFactory::WorldObjectEquipmentFactory() {

}

Weapon* WorldObjectEquipmentFactory::weapon(const std::string& name) {
    std::string type = Property<std::string>(name + ".general.type", "gun");

    if(type == "gun") {
        return new GenericGun(name);
    } else if(type == "rocketlauncher") {
        return new GenericRocketLauncher(name);
    } else {
        glow::info("No such weapon %;", name);
        exit(-1);
    }
}

Engine* WorldObjectEquipmentFactory::engine(const std::string& name) {
    std::string type = Property<std::string>(name + ".general.type", "engine");

    if(type == "engine") {
        return new GenericEngine(name);
    } else {
        glow::info("No such engine %;", name);
        exit(-1);
    }
}


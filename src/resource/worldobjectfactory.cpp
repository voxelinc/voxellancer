#include "worldobjectfactory.h"

#include <list>

#include "worldobject/hardpoint.h"
#include "worldobject/ship.h"

#include "clustercache.h"



WorldObjectFactory::WorldObjectFactory() {
    PropertyManager::instance()->load("data/worldobjects/basicship.ini", "basicship");
}

WorldObjectFactory::setupHardpoints() {
    for(Hardpoint* hardpoint : m_worldObject->components().hardpoints()) {
        std::string prefix = m_name + ".hardpoint" + std::to_string(hardpoint->index()) + ".";

        hardpoint->setDirection(Property<glm::vec3>(prefix + "direction"));
        hardpoint->setFieldOfAim(Property<glm::vec2>(prefix + "fieldOfAim"));

        std::list<std::string> mountableWeapons = Property<std::list<std::string>>(prefix + "mountable")
        for(std::string& weapon : mountableWeapons) {
            hardpoint->setMountable(weapon, true);
        }

        std::string defaultWeapon = Property<std::string>(prefix + "default");
        if(!defaultWeapon.empty()) {
            hardpoint->setWeapon(ComponentFactory::instance()->weapon(defaultWeapon));
        }
    }
}

WorldObjectFactory::setupEngineSlots() {
    for(EngineSlots* engineSlot : m_worldObject->components().engineSlots()) {
        std::string prefix = m_name + ".engingeslot" + std::to_string(engineSlot->index()) + ".";

        engineSlot->setDirection(Property<glm::vec3>(prefix + "direction"));

        std::list<std::string> mountableEngines = Property<std::list<std::string>>(prefix + "mountable")
        for(std::string& engine : mountableEngines) {
            engineSlot->setMountable(engine, true);
        }

        std::string defaultEngine = Property<std::string>(prefix + "default");
        if(!defaultEngine.empty()) {
            hardpoint->setWeapon(ComponentFactory::instance()->engine(defaultEngine));
        }
    }
}


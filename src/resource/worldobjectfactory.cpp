#include "worldobjectfactory.h"

#include <list>

#include "worldobject/components/hardpoint.h"
#include "worldobject/components/engineslot.h"
#include "worldobject/ship.h"
#include "worldobject/worldobject.h"

#include "clustercache.h"


WorldObjectFactory::WorldObjectFactory() {
    PropertyManager::instance()->load("data/worldobjects/basicship.ini", "basicship");
    PropertyManager::instance()->load("data/worldobjects/gunbullet.ini", "gunbullet");
    PropertyManager::instance()->load("data/worldobjects/torpedo.ini", "torpedo");
}

void WorldObjectFactory::setupHardpoints() {
    for(Hardpoint* hardpoint : m_worldObject->components().hardpoints()) {
        std::string prefix = m_name + ".hardpoint" + std::to_string(hardpoint->index()) + ".";

        hardpoint->setDirection(Property<glm::vec3>(prefix + "direction"));
        hardpoint->setFieldOfAim(Property<glm::vec2>(prefix + "fieldOfAim"));

        std::list<std::string> mountableWeapons = Property<std::list<std::string>>(prefix + "mountable");
        for(std::string& weapon : mountableWeapons) {
            hardpoint->setMountable(weapon, true);
        }
    }
}

void WorldObjectFactory::setupEngineSlots() {
    for(EngineSlot* engineSlot : m_worldObject->components().engineSlots()) {
        std::string prefix = m_name + ".engineslot" + std::to_string(engineSlot->index()) + ".";

        engineSlot->setDirection(Property<glm::vec3>(prefix + "direction"));

        std::list<std::string> mountableEngines = Property<std::list<std::string>>(prefix + "mountable");
        for(std::string& engine : mountableEngines) {
            engineSlot->setMountable(engine, true);
        }
    }
}


#include "worldobjectbuilder.h"

#include <cassert>

#include <glow/logging.h>

#include "property/property.h"

#include "worldobject/components/engineslot.h"
#include "worldobject/components/hardpoint.h"
#include "worldobject/components/weapons/genericbullet.h"
#include "worldobject/components/weapons/genericrocket.h"
#include "worldobject/genericship.h"
#include "worldobject/genericworldobject.h"
#include "worldobject/ship.h"
#include "worldobject/worldobject.h"

#include "clustercache.h"


WorldObjectBuilder::WorldObjectBuilder(const std::string& name):
    m_name(name)
{
}

WorldObject* WorldObjectBuilder::build() {
    std::string type = Property<std::string>(m_name + ".general.type");

    if(type == "bullet") {
        return buildBullet();
    } else if(type == "rocket") {
        return buildRocket();
    } else if(type == "ship") {
        return buildShip();
    } else if(type == "other") {
        return buildWorldObject();
    } else {
        glow::fatal("Unknown WorldObject-Type '%;'", type);
        assert(0); // Never to be reached
    }
    return nullptr;
}

Bullet* WorldObjectBuilder::buildBullet() {
    GenericBullet* bullet = newWorldObject<GenericBullet>();

    bullet->setEmissiveness(Property<float>(m_name + ".general.emissiveness", 0.0f));
    bullet->setLifetime(Property<float>(m_name + ".general.lifetime"));

    return bullet;
}

Rocket* WorldObjectBuilder::buildRocket() {
    GenericRocket* rocket = newWorldObject<GenericRocket>();

    rocket->setLifetime(Property<float>(m_name + ".general.lifetime"));

    return rocket;
}

Ship* WorldObjectBuilder::buildShip() {
    GenericShip* ship = newWorldObject<GenericShip>();
    return ship;
}

WorldObject* WorldObjectBuilder::buildWorldObject() {
    GenericWorldObject* worldObject = newWorldObject<GenericWorldObject>();
    return worldObject;
}

void WorldObjectBuilder::setupVoxelCluster(WorldObject* worldObject) {
    Property<float> scale(m_name + ".general.scale", 1.0f);
    worldObject->transform().setScale(scale);

    std::string clusterFile = Property<std::string>(m_name + ".general.voxelcluster");
    ClusterCache::instance()->fillObject(worldObject, std::string("data/voxelcluster/") + clusterFile);
}

void WorldObjectBuilder::setupComponents(WorldObjectComponents& components) {
    setupHardpoints(components);
    setupEngineSlots(components);
}

void WorldObjectBuilder::setupHardpoints(WorldObjectComponents& components) {
    for(Hardpoint* hardpoint : components.hardpoints()) {
        std::string prefix = m_name + ".hardpoint" + std::to_string(hardpoint->index()) + ".";

        hardpoint->setDirection(Property<glm::vec3>(prefix + "direction"));
        hardpoint->setFieldOfAim(Property<glm::vec2>(prefix + "fieldOfAim"));

        std::list<std::string> mountableWeapons = Property<std::list<std::string>>(prefix + "mountable");
        for(std::string& weapon : mountableWeapons) {
            hardpoint->setMountable(weapon, true);
        }
    }
}

void WorldObjectBuilder::setupEngineSlots(WorldObjectComponents& components) {
    for(EngineSlot* engineSlot : components.engineSlots()) {
        std::string prefix = m_name + ".engineslot" + std::to_string(engineSlot->index()) + ".";

        engineSlot->setDirection(Property<glm::vec3>(prefix + "direction"));

        std::list<std::string> mountableEngines = Property<std::list<std::string>>(prefix + "mountable");
        for(std::string& engine : mountableEngines) {
            engineSlot->setMountable(engine, true);
        }
    }
}


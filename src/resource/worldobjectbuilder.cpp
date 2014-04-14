#include "worldobjectbuilder.h"

#include <cassert>
#include <type_traits>

#include <glow/logging.h>

#include "property/property.h"

#include "equipment/engine.h"
#include "equipment/engineslot.h"
#include "equipment/hardpoint.h"
#include "equipment/weapon.h"
#include "equipment/weapons/genericbullet.h"
#include "equipment/weapons/genericrocket.h"
#include "equipment/weapons/splitrocket.h"
#include "worldobject/worldobjectinfo.h"
#include "worldobject/genericship.h"
#include "worldobject/genericworldobject.h"
#include "worldobject/ship.h"
#include "worldobject/worldobject.h"

#include "clustercache.h"
#include "enginebuilder.h"
#include "weaponbuilder.h"
#include "worldobject/worldobjectcomponents.h"


WorldObjectBuilder::WorldObjectBuilder(const std::string& name):
    m_name(name)
{
}

WorldObject* WorldObjectBuilder::build() {
    std::string type = Property<std::string>(m_name + ".general.type");

    if(type == "bullet") {
        return buildBullet();
    } else if (type == "rocket") {
        return buildRocket();
    } else if(type == "ship") {
        return buildShip();
    } else if(type == "other") {
        return buildWorldObject();
    } else {
        glow::fatal("Unknown WorldObject-Type '%;'", type);
        assert(0); // Never to be reached
        return nullptr;
    }
}

Bullet* WorldObjectBuilder::buildBullet() {
    GenericBullet* bullet = makeWorldObject<GenericBullet>();

    bullet->setEmissiveness(Property<float>(m_name + ".general.emissiveness", 0.0f));
    bullet->setLifetime(Property<float>(m_name + ".general.lifetime"));
    bullet->setHitSound(SoundProperties::fromProperties(m_name + ".hitsound"));

    return bullet;
}

Rocket* WorldObjectBuilder::buildRocket() {
    std::string subtype = Property<std::string>(m_name + ".general.subtype", "");
    GenericRocket* rocket;

    if (subtype == "split") {
        SplitRocket* splitRocket = makeWorldObject<SplitRocket>();

        splitRocket->setChildrenCount(Property<int>(m_name + ".special.childrenCount", 5));
        splitRocket->setChildrenType(Property<std::string>(m_name + ".special.childrenType", "hornet"));

        rocket = splitRocket;
    } else {
        rocket = makeWorldObject<GenericRocket>();
    }

    rocket->setLifetime(Property<float>(m_name + ".general.lifetime"));
    rocket->setHitSound(SoundProperties::fromProperties(m_name + ".explosionsound"));
    return rocket;
}

Ship* WorldObjectBuilder::buildShip() {
    GenericShip* ship = makeWorldObject<GenericShip>();
    if (ship->crucialVoxel() == nullptr) {
        glow::warning("WorldObjectBuilder: ship %; has no crucial voxel", m_name);
    }
    return ship;
}

WorldObject* WorldObjectBuilder::buildWorldObject() {
    GenericWorldObject* worldObject = makeWorldObject<GenericWorldObject>();
    return worldObject;
}

template<typename T>
T* WorldObjectBuilder::makeWorldObject() {
    static_assert(std::is_base_of<WorldObject, T>::value, "T needs to be derived from WorldObject");

    T* object = new T();
    WorldObject* worldObject = object;

    worldObject->info().setName(m_name);

    setupVoxelCluster(worldObject);
    setupComponents(worldObject->components());

    std::string collisionFieldOfDamageProperty = m_name + ".general.collisionFieldOfDamage";
    if (Property<std::string>(collisionFieldOfDamageProperty, "").get() == "inf") {
        worldObject->setCollisionFieldOfDamage(std::numeric_limits<float>::max());
    } else {
        worldObject->setCollisionFieldOfDamage(Property<float>(collisionFieldOfDamageProperty, glm::pi<float>() * 2));
    }

    equipSomehow(worldObject);

    return object;
}

void WorldObjectBuilder::equipSomehow(WorldObject* worldObject) {
    for (std::shared_ptr<Hardpoint> hardpoint : worldObject->components().hardpoints()) {
        if(!hardpoint->mountables().empty()) {
            Weapon* weapon = WeaponBuilder(hardpoint->mountables().front()).build();
            hardpoint->setWeapon(std::shared_ptr<Weapon>(weapon));
        }
    }
    for (std::shared_ptr<EngineSlot> engineSlot : worldObject->components().engineSlots()) {
        if(!engineSlot->mountables().empty()) {
            Engine* engine = EngineBuilder(engineSlot->mountables().front()).build();
            engineSlot->setEngine(std::shared_ptr<Engine>(engine));
        }
    }
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
    for (std::shared_ptr<Hardpoint> hardpoint : components.hardpoints()) {
        std::string prefix = m_name + ".hardpoint" + std::to_string(hardpoint->index()) + ".";

        hardpoint->setDirection(Property<glm::vec3>(prefix + "direction"));
        hardpoint->setFieldOfAim(Property<float>(prefix + "fieldOfAim"));

        std::list<std::string> mountableWeapons = Property<std::list<std::string>>(prefix + "mountable");
        for(std::string& weapon : mountableWeapons) {
            hardpoint->setMountable(weapon, true);
        }
    }
}

void WorldObjectBuilder::setupEngineSlots(WorldObjectComponents& components) {
    for (std::shared_ptr<EngineSlot> engineSlot : components.engineSlots()) {
        std::string prefix = m_name + ".engineslot" + std::to_string(engineSlot->index()) + ".";

        engineSlot->setDirection(Property<glm::vec3>(prefix + "direction"));

        std::list<std::string> mountableEngines = Property<std::list<std::string>>(prefix + "mountable");
        for(std::string& engine : mountableEngines) {
            engineSlot->setMountable(engine, true);
        }
    }
}


#include "voxelobjectbuilder.h"

#include <cassert>
#include <type_traits>

#include <glow/logging.h>

#include "bulletengine/bulletengine.h"
#include "bulletengine/instancedbullet.h"

#include "equipment/engine.h"
#include "equipment/engineslot.h"
#include "equipment/hardpoint.h"
#include "equipment/shield.h"
#include "equipment/shieldslot.h"
#include "equipment/weapon.h"
#include "equipment/weapons/bullet.h"
#include "equipment/weapons/worldobjectbullet.h"
#include "equipment/weapons/rocket.h"
#include "equipment/weapons/splitrocket.h"

#include "world/world.h"

#include "worldobject/worldobjectinfo.h"
#include "worldobject/ship.h"
#include "worldobject/worldobject.h"
#include "worldobject/worldobjectcomponents.h"

#include "clustercache.h"
#include "enginebuilder.h"
#include "shieldbuilder.h"
#include "weaponbuilder.h"


VoxelObjectBuilder::VoxelObjectBuilder(const std::string& name):
    m_name(name)
{
}

WorldObject* VoxelObjectBuilder::buildWorldObject() {
    std::string type = Property<std::string>(m_name + ".general.type");

    if(type == "bullet") {
        return buildWorldObjectBullet();
    } else if(type == "rocket") {
        return buildRocket();
    } else if(type == "ship") {
        return buildShip();
    } else if(type == "other") {
        return buildOther();
    } else {
        glow::fatal("Unknown WorldObject-Type '%;'", type);
        assert(0); // Never to be reached
        return nullptr;
    }
}

Bullet* VoxelObjectBuilder::buildBullet() {
    if (Property<bool>::get(m_name + ".general.instanced", false)) {
        return buildInstancedBullet();
    } else {
        return buildWorldObjectBullet();
    }
}

InstancedBullet* VoxelObjectBuilder::buildInstancedBullet() {
    return World::instance()->bulletEngine().createBullet(m_name);
}

WorldObjectBullet* VoxelObjectBuilder::buildWorldObjectBullet() {
    WorldObjectBullet* bullet = makeWorldObject<WorldObjectBullet>();

    bullet->setEmissiveness(Property<float>(m_name + ".general.emissiveness", 0.0f));
    bullet->setLifetime(Property<float>(m_name + ".general.lifetime"));

    bullet->setHitSound(SoundProperties::fromProperties(m_name + ".hitsound"));

    return bullet;
}

Rocket* VoxelObjectBuilder::buildRocket() {
    Rocket* rocket;

    std::string subtype = Property<std::string>(m_name + ".general.subtype", "");
    if (subtype == "split") {
        SplitRocket* splitRocket = makeWorldObject<SplitRocket>();

        splitRocket->setChildrenCount(Property<int>(m_name + ".special.childrenCount"));
        splitRocket->setChildrenType(Property<std::string>(m_name + ".special.childrenType"));
        splitRocket->setChildrenSpeedBoost(Property<float>(m_name + ".special.childrenSpeedBoost", 0.0f));
        splitRocket->setChildrenSpeedBoostRandomization(Property<float>(m_name + ".special.childrenSpeedBoostRandomization", 0.0f));
        splitRocket->setSplitDistance(Property<float>(m_name + ".special.splitDistance"));
        splitRocket->setSplitDirectionTolerance(Property<float>(m_name + ".special.splitDirectionTolerance"));
        splitRocket->setSplitAngle(Property<float>(m_name + ".special.splitAngle"));
        splitRocket->setSplitAngleRandomization(Property<float>(m_name + ".special.splitAngleRandomization", 0.0f));
        splitRocket->setMinFlytimeBeforeSplit(Property<float>(m_name + ".special.minFlytimeBeforeSplit"));

        rocket = splitRocket;
    } else {
        rocket = makeWorldObject<Rocket>();
    }

    rocket->setLifetime(Property<float>(m_name + ".general.lifetime"));
    rocket->setHitSound(SoundProperties::fromProperties(m_name + ".explosionsound"));
    return rocket;
}

Ship* VoxelObjectBuilder::buildShip() {
    Ship* ship = makeWorldObject<Ship>();

    if (ship->crucialVoxel() == nullptr) {
        glow::warning("VoxelObjectBuilder: ship %; has no crucial voxel", m_name);
    }
    if (ship->cockpitVoxels().empty()) {
        glow::warning("VoxelObjectBuilder: ship %; has no cockpit voxel(s)", m_name);
    }
    return ship;
}

WorldObject* VoxelObjectBuilder::buildOther() {
    return makeWorldObject<WorldObject>();
}

template<typename T>
T* VoxelObjectBuilder::makeWorldObject() {
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

void VoxelObjectBuilder::setupVoxelCluster(WorldObject* worldObject) {
    Property<float> scale(m_name + ".general.scale", 1.0f);
    worldObject->transform().setScale(scale);

    std::string clusterFile = Property<std::string>(m_name + ".general.voxelcluster");
    ClusterCache::instance()->fillObject(worldObject, std::string("data/voxelcluster/") + clusterFile);
}

void VoxelObjectBuilder::setupComponents(WorldObjectComponents& components) {
    setupHardpoints(components);
    setupEngineSlots(components);
    setupShieldSlots(components);
}

void VoxelObjectBuilder::setupHardpoints(WorldObjectComponents& components) {
    for (std::shared_ptr<Hardpoint> hardpoint : components.hardpoints()) {
        std::string prefix = m_name + ".hardpointGroup" + std::to_string(hardpoint->group()) + ".";

        hardpoint->setDirection(Property<glm::vec3>(prefix + "direction"));
        hardpoint->setFieldOfAim(Property<float>(prefix + "fieldOfAim"));

        std::list<std::string> mountableWeapons = Property<std::list<std::string>>(prefix + "mountable");
        for(std::string& weapon : mountableWeapons) {
            hardpoint->setMountable(weapon, true);
        }
    }
}

void VoxelObjectBuilder::setupEngineSlots(WorldObjectComponents& components) {
    for (std::shared_ptr<EngineSlot> engineSlot : components.engineSlots()) {
        std::string prefix = m_name + ".engineslotGroup" + std::to_string(engineSlot->group()) + ".";

        engineSlot->setDirection(Property<glm::vec3>(prefix + "direction"));

        std::list<std::string> mountableEngines = Property<std::list<std::string>>(prefix + "mountable");
        for(std::string& engine : mountableEngines) {
            engineSlot->setMountable(engine, true);
        }
    }
}

void VoxelObjectBuilder::setupShieldSlots(WorldObjectComponents& components) {
    for (int i = 0; PropertyManager::instance()->hasGroup(m_name + ".shieldslot" + std::to_string(i)); i++) {
        std::shared_ptr<ShieldSlot> shieldSlot = std::make_shared<ShieldSlot>(&components, i);

        std::string prefix = m_name + ".shieldslot" + std::to_string(i) + ".";
        std::list<std::string> mountableShields = Property<std::list<std::string>>(prefix + "mountable");

        for(std::string& shield : mountableShields) {
            shieldSlot->setMountable(shield, true);
        }

        components.addShieldSlot(shieldSlot);
    }
}

void VoxelObjectBuilder::equipSomehow(WorldObject* worldObject) {
    for (std::shared_ptr<Hardpoint>& hardpoint : worldObject->components().hardpoints()) {
        if(!hardpoint->mountables().empty()) {
            Weapon* weapon = WeaponBuilder(hardpoint->mountables().front()).build();
            hardpoint->setWeapon(std::shared_ptr<Weapon>(weapon));
        }
    }

    for (std::shared_ptr<EngineSlot>& engineSlot : worldObject->components().engineSlots()) {
        if(!engineSlot->mountables().empty()) {
            Engine* engine = EngineBuilder(engineSlot->mountables().front()).build();
            engineSlot->setEngine(std::shared_ptr<Engine>(engine));
        }
    }

    for (std::shared_ptr<ShieldSlot>& shieldSlot : worldObject->components().shieldSlots()) {
        if(!shieldSlot->mountables().empty()) {
            Shield* shield = ShieldBuilder(shieldSlot->mountables().front()).build();
            shieldSlot->setShield(std::shared_ptr<Shield>(shield));
        }
    }
}


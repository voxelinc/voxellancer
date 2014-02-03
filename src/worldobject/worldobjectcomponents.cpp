#include "worldobjectcomponents.h"

#include <algorithm>

#include "worldobject/components/engineslot.h"
#include "worldobject/components/engine.h"
#include "worldobject/components/hardpoint.h"
#include "worldobject/components/weapon.h"


WorldObjectComponents::WorldObjectComponents(WorldObject* worldObject):
    m_worldObject(worldObject)
{
}

WorldObject* WorldObjectComponents::worldObject() {
    return m_worldObject;
}

void WorldObjectComponents::load(const std::string& key) {
    setupHardpoints(key);
    setupEngineSlots(key);
}

void WorldObjectComponents::addEngineSlot(EngineSlot* engineSlot) {
    m_engineSlots.push_back(engineSlot);
}

void WorldObjectComponents::removeEngineSlot(EngineSlot* engineSlot) {
    m_engineSlots.remove(engineSlot);
}

EngineSlot* WorldObjectComponents::engineSlot(int index) {
    std::list<EngineSlot*>::iterator i = std::find_if(m_engineSlots.begin(), m_engineSlots.end(), [&](EngineSlot* engineSlot) {
        return engineSlot->index() == index;
    });
    return i == m_engineSlots.end() ? nullptr : *i;
}

std::list<EngineSlot*>& WorldObjectComponents::engineSlots() {
    return m_engineSlots;
}

EnginePower WorldObjectComponents::enginePower() const {
    EnginePower accumulated;
    for (EngineSlot* engineSlot : m_engineSlots) {
        if (engineSlot->engine()) {
            accumulated += engineSlot->engine()->power();
        }
    }
    return accumulated;
}

Acceleration WorldObjectComponents::currentAcceleration() const {
    Acceleration accumulated;
    for (EngineSlot* engineSlot : m_engineSlots) {
        if (engineSlot->engine()) {
            accumulated += engineSlot->engine()->currentAcceleration();
        }
    }
    return accumulated;

}

const EngineState& WorldObjectComponents::engineState() const {
    return m_engineState;
}

void WorldObjectComponents::setEngineState(const EngineState& engineState) {
    m_engineState = engineState;

    for (EngineSlot* engineSlot : m_engineSlots) {
        if (engineSlot->engine()) {
            engineSlot->engine()->setState(engineState);
        }
    }
}

void WorldObjectComponents::addHardpoint(Hardpoint* hardpoint) {
    m_hardpoints.push_back(hardpoint);
}

void WorldObjectComponents::removeHardpoint(Hardpoint* hardpoint) {
    m_hardpoints.remove(hardpoint);
}

Hardpoint* WorldObjectComponents::hardpoint(int index) {
    std::list<Hardpoint*>::iterator i = std::find_if(m_hardpoints.begin(), m_hardpoints.end(), [&](Hardpoint* hardpoint) {
        return hardpoint->index() == index;
    });
    return i == m_hardpoints.end() ? nullptr : *i;
}

std::list<Hardpoint*>& WorldObjectComponents::hardpoints() {
    return m_hardpoints;
}

void WorldObjectComponents::fireAtPoint(const glm::vec3& point) {
    for (Hardpoint* hardpoint : m_hardpoints) {
        if(!hardpoint->weapon()) {
            continue;
        }
        if (hardpoint->weapon()->aimType() == WeaponAimType::Point) {
            hardpoint->weapon()->shootAtPoint(point);
        }
    }
}

void WorldObjectComponents::fireAtObject(WorldObject* worldObject) {
    assert(worldObject);

    for (Hardpoint* hardpoint : m_hardpoints) {
        if(!hardpoint->weapon()) {
            continue;
        }
        if (hardpoint->weapon()->aimType() == WeaponAimType::Object) {
            hardpoint->weapon()->shootAtObject(worldObject);
        }
    }
}

void WorldObjectComponents::update(float deltaSec) {
    for(Hardpoint* hardpoint : m_hardpoints) {
        hardpoint->update(deltaSec);
    }

    for (EngineSlot* engineSlot : m_engineSlots) {
        engineSlot->update(deltaSec);
    }
}


void WorldObjectComponents::setupHardpoints(const std::string& key) {
    for(Hardpoint* hardpoint : m_hardpoints) {
        std::string prefix = key + ".hardpoint" + std::to_string(hardpoint->index()) + ".";

        hardpoint->setDirection(Property<glm::vec3>(prefix + "direction"));
        hardpoint->setFieldOfAim(Property<glm::vec2>(prefix + "fieldOfAim"));

        std::list<std::string> mountableWeapons = Property<std::list<std::string>>(prefix + "mountable");
        for(std::string& weapon : mountableWeapons) {
            hardpoint->setMountable(weapon, true);
        }
    }
}

void WorldObjectComponents::setupEngineSlots(const std::string& key) {
    for(EngineSlot* engineSlot : m_engineSlots) {
        std::string prefix = key + ".engineslot" + std::to_string(engineSlot->index()) + ".";

        engineSlot->setDirection(Property<glm::vec3>(prefix + "direction"));

        std::list<std::string> mountableEngines = Property<std::list<std::string>>(prefix + "mountable");
        for(std::string& engine : mountableEngines) {
            engineSlot->setMountable(engine, true);
        }
    }
}



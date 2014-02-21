#include "worldobjectcomponents.h"

#include <algorithm>

#include "equipment/engineslot.h"
#include "equipment/engine.h"
#include "equipment/hardpoint.h"
#include "equipment/weapon.h"
#include "equipment/weapons/gun.h"
#include "equipment/weapons/rocketlauncher.h"


WorldObjectComponents::WorldObjectComponents(WorldObject* worldObject):
    m_worldObject(worldObject)
{
}

WorldObject* WorldObjectComponents::worldObject() {
    return m_worldObject;
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
        if (hardpoint->weapon()->type() == WeaponType::Gun) {
            Gun& gun = dynamic_cast<Gun&>(*hardpoint->weapon().get());
            gun.fireAtPoint(point);
        }
    }
}

void WorldObjectComponents::fireAtObject(WorldObject* worldObject) {
    assert(worldObject);

    for (Hardpoint* hardpoint : m_hardpoints) {
        if(!hardpoint->weapon()) {
            continue;
        }
        if (hardpoint->weapon()->type() == WeaponType::RocketLauncher) {
            RocketLauncher& rocketLauncher = dynamic_cast<RocketLauncher&>(*hardpoint->weapon());
            rocketLauncher.fireAtObject(worldObject);
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



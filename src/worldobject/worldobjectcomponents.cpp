#include "worldobjectcomponents.h"

#include <algorithm>

#include "equipment/engineslot.h"
#include "equipment/engine.h"
#include "equipment/hardpoint.h"
#include "equipment/weapon.h"
#include "equipment/weapons/gun.h"
#include "equipment/weapons/rocketlauncher.h"

#include "worldobject.h"


WorldObjectComponents::WorldObjectComponents(WorldObject* worldObject):
    m_worldObject(worldObject),
    m_engineState(),
    m_maxSpeed(glm::vec4(50, 50, 100, 40), glm::vec3(2.f))
{
}

WorldObject* WorldObjectComponents::worldObject() {
    return m_worldObject;
}

const WorldObject* WorldObjectComponents::worldObject() const {
    return m_worldObject;
}

void WorldObjectComponents::addEngineSlot(std::shared_ptr<EngineSlot> engineSlot) {
    m_engineSlots.push_back(engineSlot);
}

void WorldObjectComponents::removeEngineSlot(const EngineSlot* engineSlot) {
    m_engineSlots.remove_if([&](std::shared_ptr<EngineSlot> slot) { return slot.get() == engineSlot; });
}

std::shared_ptr<EngineSlot> WorldObjectComponents::engineSlot(int index) {
    std::list<std::shared_ptr<EngineSlot>>::iterator i = std::find_if(m_engineSlots.begin(), m_engineSlots.end(), [&](std::shared_ptr<EngineSlot> engineSlot) {
        return engineSlot->index() == index;
    });
    return (i == m_engineSlots.end()) ? nullptr : *i;
}

std::list<std::shared_ptr<EngineSlot>>& WorldObjectComponents::engineSlots() {
    return m_engineSlots;
}

Acceleration WorldObjectComponents::currentAcceleration() {
    Acceleration acceleration = m_maxSpeed.accelerationAt(m_engineState, m_worldObject->physics());
    float aliveEngineRatio = 1.0; // this will decrease if engines get destroyed - engines could have a multiplier if it should be possible to make them more important
    
    return acceleration * aliveEngineRatio;
}

const EngineState& WorldObjectComponents::engineState() const {
    return m_engineState;
}

void WorldObjectComponents::setEngineState(const EngineState& engineState) {
    m_engineState = engineState;
}

void WorldObjectComponents::addHardpoint(std::shared_ptr<Hardpoint> hardpoint) {
    m_hardpoints.push_back(hardpoint);
}

void WorldObjectComponents::removeHardpoint(const Hardpoint* hardpoint) {
    m_hardpoints.remove_if([&](std::shared_ptr<Hardpoint> hp) { return hp.get() == hardpoint; });
}

std::shared_ptr<Hardpoint> WorldObjectComponents::hardpoint(int index) {
    std::list<std::shared_ptr<Hardpoint>>::iterator i = std::find_if(m_hardpoints.begin(), m_hardpoints.end(), [&](std::shared_ptr<Hardpoint> hardpoint) {
        return hardpoint->index() == index;
    });
    return i == m_hardpoints.end() ? nullptr : *i;
}

std::list<std::shared_ptr<Hardpoint>>& WorldObjectComponents::hardpoints() {
    return m_hardpoints;
}

void WorldObjectComponents::fireAtPoint(const glm::vec3& point) {
    for (std::shared_ptr<Hardpoint> hardpoint : m_hardpoints) {
        if (hardpoint->weapon() && hardpoint->weapon()->type() == WeaponType::Gun) {
            Gun& gun = dynamic_cast<Gun&>(*hardpoint->weapon().get());
            gun.fireAtPoint(point);
        }
    }
}

void WorldObjectComponents::fireAtObject(WorldObject* worldObject) {
    for (std::shared_ptr<Hardpoint> hardpoint : m_hardpoints) {
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
    for (std::shared_ptr<Hardpoint> hardpoint : m_hardpoints) {
        hardpoint->update(deltaSec);
    }

    for (std::shared_ptr<EngineSlot> engineSlot : m_engineSlots) {
        engineSlot->update(deltaSec);
    }
}

EnginePower WorldObjectComponents::maxSpeed() const {
    return m_maxSpeed;
}



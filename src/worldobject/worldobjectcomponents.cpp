#include "worldobjectcomponents.h"


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

void WorldObjectComponents::removeEngineVoxel(EngineSlot* engineSlot) {
    m_engineSlots.remove(engineSlot);
}

EngineSlot* WorldObjectComponents::engineSlot(int index) {
    std::list<EngineSlot*>::iterator i = m_engineSlots.find_if([](EngineSlot* engineSlot) {
        return engineSlot->index() == index;
    });
    return i == m_engineSlots.end() ? nullptr : *i;
}

std::list<EngineSlot*>& WorldObjectComponents::engineSlots() {
    return m_engineSlots;
}

Acceleration WorldObjectComponents::maxAcceleration() const {
    Acceleration accumulated;
    for (EngineSlot* engineSlot : m_engineSlots) {
        if (engineSlot->engine()) {
            accumulated += engineSlot->engine()->maxAcceleration();
        }
    }
    return accumulated;
}

const Acceleration& WorldObjectComponents::currentRelativeAcceleration() const {
    return m_currentRelativeAcceleration;
}

void WorldObjectComponents::setCurrentRelativeAcceleration(const Acceleration& currentRelativeAcceleration) {
    for (EngineSlot* engineSlot : m_engineSlots) {
        if (engineSlot->engine()) {
            engineSlot->engine()->setCurrentRelativeAcceleration(currentRelativeAcceleration);
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
    std::list<Hardpoint*>::iterator i = m_engineSlots.find_if([](Hardpoint* hardpoint) {
        return hardpoint->index() == index;
    });
    return i == m_hardpoints.end() ? nullptr : *i;
}

std::list<Hardpoint*>& WorldObjectComponents::hardpoints() {
    return m_hardpoints;
}

void WorldObjectComponents::fireAtPoint(const glm::vec3& point) {
    for (Hardpoint* hardpoint : m_hardpoints) {
        if (hardpoint->aimType() == Point) {
            hardpoint->shootAtPoint(target);
        }
    }
}

void WorldObjectComponents::fireAtObject(WorldObject* worldObject) {
    assert(worldObject);

    for (Hardpoint* hardpoint : m_hardpoints) {
        if (hardpoint->aimType() == Object) {
            hardpoint->shootAtObject(worldObject);
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


#include "engine.h"

#include "utils/tostring.h"

#include "worldobject/components/engineslot.h"
#include "worldobject/worldobject.h"


Engine::Engine(const std::string& key):
    Equipment(key),
    m_trailGenerator(this)
{
    setupTrail();
}

EngineSlot* Engine::engineSlot() {
    return m_engineSlot;
}

void Engine::setEngineSlot(EngineSlot* engineSlot) {
    m_engineSlot = engineSlot;
}

void Engine::update(float deltaSec) {
    m_trailGenerator.update(deltaSec);
}

const EngineState& Engine::state() const {
    return m_state;
}

void Engine::setState(const EngineState& state) {
    m_state = state;
}

Acceleration Engine::currentAcceleration() const {
    WorldObject* worldObject = m_engineSlot ? m_engineSlot->components()->worldObject() : nullptr;
    return worldObject ?
        Acceleration(power().accelerationAt(m_state) / worldObject->physics().mass()) :
        Acceleration();
}

void Engine::setupTrail() {
    m_trailGenerator.setLifetime(Property<float>(equipmentKey() + ".trail.lifetime"));
}


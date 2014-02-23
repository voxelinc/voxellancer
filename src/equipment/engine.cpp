#include "engine.h"

#include "utils/tostring.h"

#include "equipment/engineslot.h"

#include "physics/physics.h"

#include "voxeleffect/enginetrailgenerator.h"

#include "worldobject/worldobject.h"
#include "worldobject/worldobjectcomponents.h"


Engine::Engine(const std::string& key):
    Equipment(key),
    m_trailGenerator(new EngineTrailGenerator(this))
{
    setupTrail();
}

Engine::~Engine() = default;

EngineSlot* Engine::engineSlot() {
    return m_engineSlot;
}

void Engine::setEngineSlot(EngineSlot* engineSlot) {
    m_engineSlot = engineSlot;
}

void Engine::update(float deltaSec) {
    m_trailGenerator->update(deltaSec);
}

const EngineState& Engine::state() const {
    return m_state;
}

void Engine::setState(const EngineState& state) {
    m_state = state;
}

Acceleration Engine::currentAcceleration() const {
    WorldObject* worldObject = (m_engineSlot ? m_engineSlot->components()->worldObject() : nullptr);
    if (worldObject) {
        return Acceleration(power().accelerationAt(m_state) / worldObject->physics().mass());
    } else {
        return Acceleration();
    }
}

void Engine::setupTrail() {
    m_trailGenerator->setLifetime(Property<float>(equipmentKey() + ".trail.lifetime"));
}


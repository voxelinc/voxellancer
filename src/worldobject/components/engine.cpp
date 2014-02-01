#include "engine.h"


Engine::Engine():
    m_trailGenerator(this)
{
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

const Acceleration& Engine::currentRelativeAcceleration() const {
    return m_currentRelativeAcceleration;
}

void Engine::setCurrentRelativeAcceleration(const Acceleration& currentRelativeAcceleration) {
    m_currentRelativeAcceleration = currentRelativeAcceleration;
}

Acceleration Engine::currentAcceleration() const {
    return m_currentRelativeAcceleration * maxAcceleration();
}


#include "genericengine.h"

GenericEngine::GenericEngine(const std::string& equipmentKey):
    Engine(equipmentKey)
{
}

const Visuals& GenericEngine::visuals() const {
    return m_visuals;
}

void GenericEngine::setVisuals(const Visuals& visuals) {
    m_visuals = visuals;
}

const SoundProperties& GenericEngine::sound() const {
    return m_engineSound;
}

void GenericEngine::setEngineSound(const SoundProperties& engineSound) {
    m_engineSound = engineSound;
}

//EnginePower GenericEngine::power() const {
//    return m_power;
//}
//
//void GenericEngine::setPower(const EnginePower& power) {
//    m_power = power;
//}

void GenericEngine::update(float deltaSec) {
    Engine::update(deltaSec);
}

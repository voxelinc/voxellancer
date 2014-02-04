#include "genericengine.h"


GenericEngine::GenericEngine(const std::string& propertyPrefix):
    Engine(propertyPrefix),
    GenericEntity(propertyPrefix),
    m_directionalAcceleration(propertyPrefix + ".general.directionalAcceleration"),
    m_angularAcceleration(propertyPrefix + ".general.angularAcceleration")
{
}

EnginePower GenericEngine::power() const {
    return EnginePower(
        m_directionalAcceleration,
        m_angularAcceleration
    );
}

void GenericEngine::update(float deltaSec) {
    Engine::update(deltaSec);
}

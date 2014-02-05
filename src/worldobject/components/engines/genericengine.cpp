#include "genericengine.h"


GenericEngine::GenericEngine(const std::string& propertyPrefix):
    Engine(propertyPrefix),
    GenericEntity(propertyPrefix),
    m_directionalAcceleration(propertyPrefix + ".general.directionalAcceleration"),
    m_angularAcceleration(propertyPrefix + ".general.angularAcceleration"),
    m_color(propertyPrefix + ".visuals.color"),
    m_emissiveness(propertyPrefix + ".visuals.emissiveness")
{
    std::cout << "Engine: " << this << propertyPrefix << std::endl;
}

Visuals GenericEngine::visuals() const {
    return Visuals(
        m_color,
        m_emissiveness
    );
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


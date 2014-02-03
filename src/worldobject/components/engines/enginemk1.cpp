#include "enginemk1.h"

#include "property/property.h"



EngineMK1::EngineMK1():
    Engine("enginemk1"),
    m_directionalAcceleration("enginemk1.general.directionalAcceleration"),
    m_angularAcceleration("enginemk1.general.angularAcceleration")
{
}

EnginePower EngineMK1::power() const {
    return EnginePower(
        m_directionalAcceleration,
        m_angularAcceleration
    );
}

void EngineMK1::update(float deltaSec) {
    Engine::update(deltaSec);
}


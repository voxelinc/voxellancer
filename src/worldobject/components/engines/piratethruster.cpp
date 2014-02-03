#include "piratethruster.h"

#include "property/property.h"



PirateThruster::PirateThruster():
    Engine("piratethruster"),
    m_directionalAcceleration("piratethruster.general.directionalAcceleration"),
    m_angularAcceleration("piratethruster.general.angularAcceleration")
{
}

EnginePower PirateThruster::power() const {
    return EnginePower(
        m_directionalAcceleration.get(),
        m_angularAcceleration.get()
    );
}

void PirateThruster::update(float deltaSec) {
    Engine::update(deltaSec);
}


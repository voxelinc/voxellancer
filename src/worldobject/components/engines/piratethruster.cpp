#include "enginemk1.h"

#include "property/property.h"

#include "worldobject/components/acceleration.h"


PirateThruster::PirateThruster():
    m_directionalAcceleration("piratethruster.general.directionalAcceleration"),
    m_angularAcceleration("piratethruster.general.angularAcceleration")
{
}

Acceleration PirateThruster::maxAcceleration() const {
    return Acceleration(
        m_directionalAcceleration,
        m_angularAcceleration
    );
}

void PirateThruster::update(float deltaSec) {

}


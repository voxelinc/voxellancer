#include "enginemk1.h"

#include "property/property.h"

#include "worldobject/components/acceleration.h"


EngineMK1::EngineMK1():
    m_directionalAcceleration("enginemk1.general.directionalAcceleration"),
    m_angularAcceleration("enginemk1.general.angularAcceleration")
{
}

Acceleration EngineMK1::maxAcceleration() const {
    return Acceleration(
        m_directionalAcceleration,
        m_angularAcceleration
    );
}

void EngineMK1::update(float deltaSec) {

}


#pragma once

#include <list>

#include "physics/impulse.h"
#include "property/property.h"


class Impulsor {
public:
    Impulsor();

    void parse(std::list<Impulse>& worldObjectImpulses);


protected:
    Property<float> m_rotationFactor;
    Property<float> m_elasticity;
};

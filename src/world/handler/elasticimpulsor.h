#pragma once

#include <list>

#include "physics/impulse.h"

#include "property/property.h"


class ElasticImpulsor {
public:
    ElasticImpulsor();

    void parse(std::list<Impulse>& worldObjectImpulses);


protected:
    Property<float> m_rotationFactor;
};

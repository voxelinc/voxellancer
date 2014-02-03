#pragma once

#include <memory>

#include "property/property.h"


class Metrics {
public:
    Metrics();

    static std::shared_ptr<Metrics> instance();

    float gameUnit();
    void setGameUnit(float gameUnit);

    float toGameUnits(float metre);
    float toMetres(float gameUnits);


protected:
    static std::weak_ptr<Metrics> s_instance;

    Property<float> m_gameUnit;
};


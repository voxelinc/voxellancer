#pragma once

#include <memory>


class Metrics {
public:
    static float gameUnit();
    static void setGameUnit(float gameUnit);

    static float toGameUnits(float metre);
    static float toMetres(float gameUnits);


protected:
    static float s_gameUnit;
};


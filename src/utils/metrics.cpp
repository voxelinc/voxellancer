#include "metrics.h"


float Metrics::s_gameUnit = 2.5f;


float Metrics::gameUnit() {
    return s_gameUnit;
}

void Metrics::setGameUnit(float gameUnit) {
    s_gameUnit = gameUnit;
}

float Metrics::toGameUnits(float metre) {
    return metre / s_gameUnit;
}

float Metrics::toMetres(float gameUnits) {
    return gameUnits * s_gameUnit;
}


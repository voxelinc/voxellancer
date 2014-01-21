#include "metrics.h"


std::weak_ptr<Metrics> Metrics::s_instance;

Metrics::Metrics():
    m_gameUnit("general.unitInMetres")
{
}

std::shared_ptr<Metrics> Metrics::instance() {
    if (std::shared_ptr<Metrics> renderer = s_instance.lock()) {
        return renderer;
    } else {
        renderer = std::shared_ptr<Metrics>(new Metrics());
        s_instance = renderer;
        return renderer;
    }
}

float Metrics::gameUnit() {
    return m_gameUnit;
}

void Metrics::setGameUnit(float gameUnit) {
    m_gameUnit.set(gameUnit);
}

float Metrics::toGameUnits(float metre) {
    return metre / m_gameUnit;
}

float Metrics::toMetres(float gameUnits) {
    return gameUnits * m_gameUnit;
}


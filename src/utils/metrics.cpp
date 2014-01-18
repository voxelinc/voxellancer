#include "metrics.h"


std::weak_ptr<Metrics> Metrics::s_instance;

Metrics::Metrics():
    m_gameUnit(2.5f)
{

}

std::shared_ptr<Metrics> Metrics::instance() {
    std::shared_ptr<Metrics> metrics = s_instance.lock();
    if (!metrics) {
        metrics = std::shared_ptr<Metrics>(new Metrics());
        s_instance = metrics;
    }
    return metrics;
}

float Metrics::gameUnit() const {
    return m_gameUnit;
}

void Metrics::setGameUnit(float gameUnit) {
    m_gameUnit = gameUnit;
}

float Metrics::toGameUnits(float metre) {
    return metre / m_gameUnit;
}

float Metrics::toMetres(float gameUnits) {
    return gameUnits * m_gameUnit;
}


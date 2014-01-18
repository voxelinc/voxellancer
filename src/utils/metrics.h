#pragma once

#include <memory>


class Metrics {
public:
    Metrics();

    static std::shared_ptr<Metrics> instance();

    float gameUnit() const;
    void setGameUnit(float gameUnit);

    float toGameUnits(float metre);
    float toMetres(float gameUnits);


protected:
    float m_gameUnit;

    static std::weak_ptr<Metrics> s_instance;
};


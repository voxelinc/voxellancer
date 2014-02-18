#pragma once

#include "property/property.h"

#include "display/rendering/visuals.h"

#include "worldobject/components/engine.h"


class GenericEngine: public Engine {
public:
    GenericEngine(const std::string& equipmentKey);

    virtual Visuals visuals() const override;
    void setVisuals(const Visuals& visuals);

    virtual EnginePower power() const override;
    void setPower(const EnginePower& power);

    virtual void update(float deltaSec) override;


protected:
    EnginePower m_power;
    Visuals m_visuals;
};


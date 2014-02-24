#pragma once

#include "property/property.h"

#include "display/rendering/visuals.h"
#include "sound/soundproperties.h"

#include "worldobject/components/engine.h"


class GenericEngine: public Engine {
public:
    GenericEngine(const std::string& equipmentKey);

    virtual const Visuals& visuals() const override;
    void setVisuals(const Visuals& visuals);

    virtual const SoundProperties& sound() const override;
    void setEngineSound(const SoundProperties& engineSound);

    virtual EnginePower power() const override;
    void setPower(const EnginePower& power);

    virtual void update(float deltaSec) override;


protected:
    EnginePower m_power;
    Visuals m_visuals;
    SoundProperties m_engineSound;
};


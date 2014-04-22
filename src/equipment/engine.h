#pragma once

#include <memory>
#include <string>

#include <glm/glm.hpp>

#include "display/rendering/visuals.h"

#include "sound/soundproperties.h"

#include "enginepower.h"
#include "enginestate.h"
#include "equipment.h"


class EngineSlot;
class EngineTrailGenerator;
class Sound;

class Engine: public Equipment {
public:
    Engine(const std::string& equipmentKey);
    virtual ~Engine();

    const Visuals& visuals() const;
    void setVisuals(const Visuals& visuals);

    const SoundProperties& sound() const;
    void setEngineSound(const SoundProperties& engineSound);

    EnginePower power() const;
    void setPower(const EnginePower& power);

    EngineSlot* engineSlot();
    const EngineSlot* engineSlot() const;
    void setEngineSlot(EngineSlot* engineSlot);

    const EngineState& state() const;
    void setState(const EngineState& state);

    Acceleration currentAcceleration() const;

    virtual void update(float deltaSec);


protected:
    std::unique_ptr<EngineTrailGenerator> m_trailGenerator;
    std::shared_ptr<Sound> m_sound;
    EngineSlot* m_engineSlot;
    EngineState m_state;
    EnginePower m_power;
    Visuals m_visuals;
    SoundProperties m_engineSound;


    void setupTrail();
};


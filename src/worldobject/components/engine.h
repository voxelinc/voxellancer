#pragma once

#include <memory>
#include <string>

#include <glm/glm.hpp>

#include "enginepower.h"
#include "enginestate.h"
#include "equipment.h"


class EngineSlot;
class EngineTrailGenerator;
class Visuals;
class SoundProps;
class Sound;

class Engine: public Equipment {
public:
    Engine(const std::string& equipmentKey);
    virtual ~Engine();

    virtual const Visuals& visuals() const = 0;
    virtual const SoundProps& engineSound() const = 0;
    
    EngineSlot* engineSlot();
    void setEngineSlot(EngineSlot* engineSlot);

    virtual EnginePower power() const = 0;

    const EngineState& state() const;
    void setState(const EngineState& state);

    Acceleration currentAcceleration() const;

    virtual void update(float deltaSec);


protected:
    std::unique_ptr<EngineTrailGenerator> m_trailGenerator;
    std::shared_ptr<Sound> m_sound;
    EngineSlot* m_engineSlot;
    EngineState m_state;
    

    void setupTrail();
};


#pragma once

#include <string>

#include <glm/glm.hpp>

#include "voxeleffect/enginetrailgenerator.h"

#include "enginepower.h"
#include "enginestate.h"
#include "equipment.h"


class EngineSlot;

class Engine: public Equipment {
public:
    Engine(const std::string& equipmentKey);

    EngineSlot* engineSlot();
    void setEngineSlot(EngineSlot* engineSlot);

    virtual EnginePower power() const = 0;

    const EngineState& state() const;
    void setState(const EngineState& state);

    Acceleration currentAcceleration() const;

    virtual void update(float deltaSec);


private:
    EngineSlot* m_engineSlot;
    EngineState m_state;
    EngineTrailGenerator m_trailGenerator;

    void setupTrail();
};


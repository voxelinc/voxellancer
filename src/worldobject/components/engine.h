#pragma once

#include <glm/glm.hpp>

#include "voxeleffect/enginetrailgenerator.h"

#include "acceleration.h"


class EngineSlot;

class Engine {
public:
    Engine();

    EngineSlot* engineSlot();
    void setEngineSlot(EngineSlot* engineSlot);

    virtual Acceleration maxAcceleration() const = 0;

    const Acceleration& currentRelativeAcceleration() const;
    void setCurrentRelativeAcceleration(const Acceleration& currentRelativeAcceleration);

    Acceleration currentAcceleration() const;

    virtual void update(float deltaSec);


private:
    EngineSlot* m_engineSlot;
    Acceleration m_currentRelativeAcceleration;
    EngineTrailGenerator m_trailGenerator;
};


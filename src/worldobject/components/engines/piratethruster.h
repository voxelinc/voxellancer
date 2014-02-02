#pragma once

#include "worldobject/components/enginepower.h"
#include "worldobject/components/engine.h"


class PirateThruster: public Engine {
public:
    PirateThruster();

    virtual EnginePower power() const override;

    virtual void update(float deltaSec) override;


protected:
    Property<glm::vec4> m_directionalAcceleration;
    Property<glm::vec3> m_angularAcceleration;
};


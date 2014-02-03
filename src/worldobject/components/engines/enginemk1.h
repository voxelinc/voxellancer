#pragma once

#include "worldobject/components/engine.h"
#include "worldobject/components/enginepower.h"


class EngineMK1: public Engine {
public:
    EngineMK1();

    virtual EnginePower power() const override;

    virtual void update(float deltaSec) override;


protected:
    Property<glm::vec4> m_directionalAcceleration;
    Property<glm::vec3> m_angularAcceleration;
};

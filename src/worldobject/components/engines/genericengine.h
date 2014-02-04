#pragma once

#include "property/property.h"

#include "utils/genericentity.h"

#include "worldobject/components/engine.h"


class GenericEngine: public Engine, public GenericEntity {
public:
    GenericEngine(const std::string& propertyPrefix);

    virtual EnginePower power() const override;

    virtual void update(float deltaSec) override;


protected:
    Property<glm::vec4> m_directionalAcceleration;
    Property<glm::vec3> m_angularAcceleration;
};


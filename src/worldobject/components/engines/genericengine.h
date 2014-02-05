#pragma once

#include "property/property.h"

#include "utils/genericentity.h"

#include "worldobject/components/engine.h"


class GenericEngine: public Engine, public GenericEntity {
public:
    GenericEngine(const std::string& propertyPrefix);

    virtual Visuals visuals() const;

    virtual EnginePower power() const override;

    virtual void update(float deltaSec) override;


protected:
    Property<glm::vec4> m_directionalAcceleration;
    Property<glm::vec3> m_angularAcceleration;
    Property<uint32_t> m_color;
    Property<float> m_emissiveness;
};


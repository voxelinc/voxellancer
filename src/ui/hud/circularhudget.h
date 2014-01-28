#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "hudget.h"


class CircularHudget: public Hudget {
public:
    CircularHudget(HUD* hud, float radius);

    float radius() const;

    virtual bool isAt(const Ray& ray) const override;


protected:
    float m_radius;
};


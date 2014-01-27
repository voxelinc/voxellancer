#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "hudgetclickable.h"


class CircularHudget: public HudgetClickable {
public:
    CircularHudget();

    float radius() const;
    void setRadius(float radius);

    const glm::vec3& position() const;
    /*
        Set the position, in worldcoordinates
    */
    void setPosition(const glm::vec3& position);

    glm::vec3 direction() const;

    virtual bool isAt(const glm::quat& quat) const override;


protected:
    float m_radius;
    glm::vec3 m_position;
};


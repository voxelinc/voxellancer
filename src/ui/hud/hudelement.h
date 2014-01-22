#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>


class HUD;

class HUDElement {
public:
    HUDElement(HUD* hud);


protected:
    HUD* m_hud;
    float m_relativeRadiusFactor;
    glm::quat m_orientation;
};


#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "targetguidearrow.h"


class HUD;
class WorldObject;

class TargetGuide {
public:
    TargetGuide(HUD* hud);

    HUD* hud();

    void update(float deltaSec);
    void draw();


protected:
    HUD* m_hud;
    std::vector<TargetGuideArrow*> m_arrows;


    WorldObject* target();
    glm::quat orientationToTarget();
    void adjustArrowCount();
    void adjustArrows();
};


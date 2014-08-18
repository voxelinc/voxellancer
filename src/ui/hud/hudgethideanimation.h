#pragma once

#include "hudgetanimation.h"

/**
 * Animation that hides a hudget after a given time
 */
class HudgetHideAnimation : public HudgetAnimation {
public:
    HudgetHideAnimation(Hudget& hudget);

    void hideIn(float deltaSec);

    void update(float deltaSec);


protected:
    float m_countdown;
};


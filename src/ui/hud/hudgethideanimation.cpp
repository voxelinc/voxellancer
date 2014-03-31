#include "hudgethideanimation.h"

#include <algorithm>

#include "hudget.h"


HudgetHideAnimation::HudgetHideAnimation(Hudget& hudget):
    HudgetAnimation(hudget),
    m_countdown(0.0f)
{
}

void HudgetHideAnimation::hideIn(float deltaSec) {
    hudget().setVisible(true);
    m_countdown = deltaSec;
    setActive(true);
}

void HudgetHideAnimation::update(float deltaSec) {
    if (active()) {
        m_countdown = std::max(m_countdown - deltaSec, 0.0f);

        if (m_countdown == 0.0f) {
            hudget().setVisible(false);
            setActive(false);
        }
    }
}

#include "hudgetanimation.h"

#include "hudget.h"


HudgetAnimation::HudgetAnimation(Hudget& hudget):
    m_hudget(hudget),
    m_active(false)
{

}

Hudget& HudgetAnimation::hudget() {
    return m_hudget;
}

bool HudgetAnimation::active() const {
    return m_active;
}

void HudgetAnimation::setActive(bool active) {
    m_active = active;
}

void HudgetAnimation::update(float deltaSec) {

}


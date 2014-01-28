#include "targetguidehudget.h"

#include "hud.h"


TargetGuideHudget::TargetGuideHudget(HUD* hud):
    Hudget(hud)
{
}

glm::vec3 TargetGuideHudget::position() const {

}

glm::quat TargetGuideHudget::orientation() const {

}

void TargetGuideHudget::update(float deltaSec) {
    setVisible(target() != nullptr);

    if(target()) {
        adjustArrowCount();
        adjustArrows();
    }
}

void TargetGuideHudget::draw() {
    for(TargetGuideArrow& arrow : m_arrows) {
        arrow.draw();
    }
}


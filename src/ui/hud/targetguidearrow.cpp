#include "targetguidearrow.h"

#include "targetguide.h"
#include "hud.h"


TargetGuideArrow::TargetGuideArrow(TargetGuide* targetGuide):
    Hudget(targetGuide->hud()),
    m_targetGuide(targetGuide),
    m_voxels(this)
{
}

void TargetGuideArrow::setTargetOrientation(const glm::quat& targetOrientation) {
    m_targetOrientation = targetOrientation;
}

void TargetGuideArrow::setRelativeOrientation(const glm::quat& relativeOrientation) {
    m_relativeOrientation = relativeOrientation;
}

glm::vec3 TargetGuideArrow::position() const {
    HUD* hud = m_targetGuide->hud();
    return hud->position() + (hud->orientation() * m_relativeOrientation * glm::vec3(0, 0, -hud->sphere().radius()));
}

glm::quat TargetGuideArrow::orientation() const {
    return m_targetGuide->hud()->orientation() * m_relativeOrientation;
}

void TargetGuideArrow::update(float deltaSec) {

}

void TargetGuideArrow::draw() {
    m_voxels.draw();
}


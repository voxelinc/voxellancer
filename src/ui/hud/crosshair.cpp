#include "crosshair.h"

#include "camera/camerahead.h"
#include "camera/cameradolly.h"

#include "hud.h"


CrossHair::CrossHair(HUD* hud):
    Hudget(hud),
    m_voxels(this)
{

}

bool CrossHair::actionActive() const {
    return m_actionActive;
}

void CrossHair::setActionActive(bool actionActive) {
    m_actionActive = actionActive;
}

void CrossHair::update(float deltaSec) {

}

void CrossHair::draw() {
    m_voxels.draw();
}


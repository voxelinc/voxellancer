#include "arrowhudget.h"

#include <cmath>

#include <glm/glm.hpp>

#include "utils/geometryhelper.h"
#include "hudobjectdelegate.h"
#include "hud.h"
#include "worldobject/worldobject.h"


ArrowHudget::ArrowHudget(HUD* hud, HUDObjectDelegate* objectDelegate) :
    Hudget(hud),
    m_objectDelegate(objectDelegate),
    m_voxels(this)
{

}

void ArrowHudget::update(float deltaSec) {
    WorldObject* worldObject = m_objectDelegate->worldObject();

    if(worldObject) {
        pointToWorldPoint(worldObject->transform().position());
    }
}

void ArrowHudget::draw() {
    m_voxels.draw();
}

void ArrowHudget::setTarget(bool target) {
    m_voxels.setTarget(target);
}
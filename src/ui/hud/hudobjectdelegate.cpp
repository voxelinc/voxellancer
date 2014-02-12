#include "hudobjectdelegate.h"

#include "worldobject/worldobject.h"

#include "hud.h"
#include "hudget.h"
#include "objecthudget.h"
#include "arrowhudget.h"


HUDObjectDelegate::HUDObjectDelegate(HUD* hud, WorldObject* worldObject):
    m_hud(hud),
    m_worldObjectHandle(worldObject->handle()),
    m_target(false),
    m_objectHudget(new ObjectHudget(m_hud, this)),
    m_arrowHudget(new ArrowHudget(m_hud, this))
{
}

HUD* HUDObjectDelegate::hud() {
    return m_hud;
}

WorldObject* HUDObjectDelegate::worldObject() {
    return m_worldObjectHandle.get();
}

Hudget* HUDObjectDelegate::objectHudget() {
    return m_objectHudget;
}

Hudget* HUDObjectDelegate::arrowHudget() {
    return m_arrowHudget;
}

bool HUDObjectDelegate::isTarget() {
    return m_target;
}

void HUDObjectDelegate::setTarget(bool target) {
    m_arrowHudget->setTarget(target);
    m_target = target;
}
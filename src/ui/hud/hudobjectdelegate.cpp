#include "hudobjectdelegate.h"

#include "worldobject/worldobject.h"

#include "hud.h"
#include "hudget.h"
#include "objecthudget.h"


HUDObjectDelegate::HUDObjectDelegate(HUD* hud, WorldObject* worldObject):
    m_hud(hud),
    m_worldObjectHandle(worldObject->handle()),
    m_objectHudget(new ObjectHudget(m_hud, this))
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
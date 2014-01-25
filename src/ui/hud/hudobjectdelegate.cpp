#include "hudobjectdelegate.h"

#include "worldobject/worldobject.h"

#include "hud.h"
#include "hudget.h"
#include "objectdelegatehudget.h"


HUDObjectDelegate::HUDObjectDelegate(HUD* hud, WorldObject* worldObject):
    m_hud(hud),
    m_worldObjectHandle(worldObject->handle()),
    m_hudget(new ObjectDelegateHudget(m_hud, this))
{
}

HUD* HUDObjectDelegate::hud() {
    return m_hud;
}

WorldObject* HUDObjectDelegate::worldObject() {
    return m_worldObjectHandle.get()->get();
}

Hudget* HUDObjectDelegate::hudget() {
    return m_hudget;
}

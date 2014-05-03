#include "hudobjectdelegate.h"

#include "worldobject/worldobject.h"

#include "hud.h"
#include "hudget.h"
#include "objecthudget.h"


HUDObjectDelegate::HUDObjectDelegate(HUD* hud, WorldObject* worldObject, ObjectHudget* hudget):
    m_hud(hud),
    m_worldObjectHandle(makeHandle(worldObject)),
    m_hudget(hudget)
{
    hudget->setObjectDelegate(this);
}

HUD* HUDObjectDelegate::hud() {
    return m_hud;
}

WorldObject* HUDObjectDelegate::worldObject() {
    return m_worldObjectHandle.get();
}

ObjectHudget* HUDObjectDelegate::hudget() {
    return m_hudget;
}


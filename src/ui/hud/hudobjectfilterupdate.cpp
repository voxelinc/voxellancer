#include "hudobjectfilterupdate.h"

#include <iostream>

#include "worldobject/worldobject.h"

#include "hud.h"
#include "hudobjectdelegate.h"


HUDObjectFilterUpdate::HUDObjectFilterUpdate(HUD* hud, const std::set<WorldObject*>& newWorldObjects, const std::set<WorldObject*>& obsoleteWorldObjects):
    m_hud(hud),
    m_newWorldObjects(newWorldObjects),
    m_obsoleteWorldObjects(obsoleteWorldObjects)
{
}

void HUDObjectFilterUpdate::apply() {
    for(WorldObject* worldObject : m_newWorldObjects) {
        HUDObjectDelegate* objectDelgate = new HUDObjectDelegate(m_hud, worldObject);
        m_hud->addObjectDelegate(objectDelgate);
    }

    for(WorldObject* worldObject : m_obsoleteWorldObjects) {
        HUDObjectDelegate* objectDelgate = m_hud->objectDelegate(worldObject);
        m_hud->removeObjectDelegate(objectDelgate);
    }
}



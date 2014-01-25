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
    if(m_newWorldObjects.size() > 0) {
        std::cout << "New: ";
        for(WorldObject* wo : newWorldObjects) {
            std::cout << wo->objectInfo().name() << " ";
        }
        std::cout << std::endl;
    }

    if(m_obsoleteWorldObjects.size() > 0) {
            std::cout << "Obsolete: ";
        for(WorldObject* wo : obsoleteWorldObjects) {
            std::cout << wo->objectInfo().name() << " ";
        }
        std::cout << std::endl;
    }
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



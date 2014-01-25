#include "hudobjectfilterupdate.h"

#include <set>

#include "geometry/sphere.h"

#include "worldtree/worldtreequery.h"
#include "worldtree/worldtreegeode.h"

#include "world/world.h"

#include "player.h"

#include "hud.h"
#include "hudobjectdelegate.h"


static float SCAN_RADIUS = 20.0f;

HUDObjectFilter::HUDObjectFilter(HUD* hud):
    m_hud(hud)
{
}

HUDObjectFilterUpdate HUDObjectFilter::filterUpdate() {
    Sphere scanSphere(m_hud->position(), SCAN_RADIUS);

    std::set<WorldTreeGeode*> geodes = WorldTreeQuery(&World::instance()->worldTree(), &scanSphere, nullptr, m_hud->player()->playerShip()).nearGeodes();
    std::list<HUDObjectDelegate*> currentObjectDelegates = m_hud->objectDelegates();
    std::set<WorldObject*> currentWorldObjects;
    std::set<WorldObject*> newWorldObjects;

    for(HUDObjectDelegate* objectDelegate : currentObjectDelegates) {
        currentWorldObjects.insert(objectDelegate->worldObject());
    }

    for(std::set<WorldTreeGeode*>::iterator i = geodes.begin(); i != geodes.end(); ++i) {
        WorldTreeGeode* geode = *i;
        WorldObject* worldObject = geode->worldObject();

        std::set<WorldObject*>::iterator j = currentWorldObjects.find(worldObject);

        if(j == currentWorldObjects.end()) {
            newWorldObjects.insert(worldObject);
        } else {
            currentWorldObjects.erase(worldObject);
        }
    }

    return HUDObjectFilterUpdate(m_hud, newWorldObjects, currentWorldObjects);
}

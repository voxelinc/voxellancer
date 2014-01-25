#pragma once

#include <algorithm>
#include <list>
#include <set>
#include <vector>

#include "display/viewer.h"

#include "geometry/sphere.h"

#include "property/property.h"

#include "crosshair.h"
#include "hudobjectfilter.h"


class Player;
class Hudget;
class WorldObject;
class HUDObjectDelegate;

class HUD {
public:
    HUD(Player* player, Viewer* viewer);

    Player* player();
    const Sphere& sphere() const;

    CrossHair& crossHair();

    glm::vec3 position() const;
    glm::quat orientation() const;

    void addHudget(Hudget* hudget);
    void removeHudget(Hudget* hudget);

    void addObjectDelegate(HUDObjectDelegate* objectDelegate);
    void removeObjectDelegate(HUDObjectDelegate* objectDelegate);

    const std::list<HUDObjectDelegate*>& objectDelegates() const;
    HUDObjectDelegate* objectDelegate(WorldObject* worldObject);

    void setCrossHairOffset(const glm::vec2& mousePosition);

    void update(float deltaSec);
    void draw();


protected:
    Player* m_player;
    Viewer* m_viewer;
    Sphere m_sphere;

    CrossHair m_crossHair;

    std::list<Hudget*> m_hudgets;

    HUDObjectFilter m_objectFilter;
    std::list<HUDObjectDelegate*> m_objectDelegates;
};


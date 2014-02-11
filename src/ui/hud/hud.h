#pragma once

#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <vector>

#include "display/viewer.h"

#include "geometry/sphere.h"

#include "property/property.h"

#include "worldtree/worldtreescanner.h"

#include "crosshair.h"
#include "aimhelperhudget.h"



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
    AimHelperHudget& aimHelper();

    glm::vec3 centerOfView() const;
    glm::vec3 position() const;
    glm::quat orientation() const;

    void addHudget(Hudget* hudget);
    void removeHudget(Hudget* hudget);

    void addObjectDelegate(HUDObjectDelegate* objectDelegate);
    void removeObjectDelegate(HUDObjectDelegate* objectDelegate);

    HUDObjectDelegate* objectDelegate(WorldObject* worldObject);

    void setCrossHairOffset(const glm::vec2& mousePosition);

    void onClick(int button);

    void update(float deltaSec);
    void draw();


protected:
    Player* m_player;
    Viewer* m_viewer;
    Sphere m_sphere;

    CrossHair m_crossHair;
    AimHelperHudget m_aimHelper;

    std::list<Hudget*> m_hudgets;

    WorldTreeScanner m_scanner;
    std::map<WorldObject*, HUDObjectDelegate*> m_objectDelegates;


    void updateScanner(float deltaSec);
};


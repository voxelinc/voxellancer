#pragma once

#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <vector>

#include "geometry/sphere.h"

#include "property/property.h"


class Player;
class Hudget;
class WorldObject;
class HUDObjectDelegate;
class AimHelperHudget;
class Viewer;
class WorldTreeScanner;
class CrossHair;

class HUD {
public:
    HUD(Player* player, Viewer* viewer);
    ~HUD();

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

    void update(float deltaSec);
    void draw();


protected:
    Player* m_player;
    Viewer* m_viewer;
    Sphere m_sphere;

    std::unique_ptr<AimHelperHudget> m_aimHelper;
    std::unique_ptr<CrossHair> m_crossHair;
    std::unique_ptr<WorldTreeScanner> m_scanner;

    std::list<Hudget*> m_hudgets;

    std::map<WorldObject*, HUDObjectDelegate*> m_objectDelegates;

    void updateScanner(float deltaSec);
};


#pragma once

#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <vector>

#include "geometry/sphere.h"

#include "property/property.h"
#include "worldobject/handle/handle.h"

enum class ClickType {
    None,
    Selection
};


class Player;
class Hudget;
class WorldObject;
class HUDObjectDelegate;
class AimHelperHudget;
class Viewer;
class WorldTreeScanner;
class CrossHair;
class TextFieldHudget;
class ButtonHudget;

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

    void setTarget(WorldObject* target);
    WorldObject* target();

    void onClick(ClickType clickType);

    void update(float deltaSec);
    void draw();

    glm::vec3 applyTo(const glm::vec3 &vertex) const;
	
    Viewer* viewer() const;

    float fovy() const;
    float fovx() const;

protected:
    Player* m_player;
    Viewer* m_viewer;
    Sphere m_sphere;
    Handle<WorldObject> m_target;

    float m_fovy, m_fovx;

    std::unique_ptr<AimHelperHudget> m_aimHelper;
    std::unique_ptr<CrossHair> m_crossHair;
    std::unique_ptr<WorldTreeScanner> m_scanner;
    std::unique_ptr<TextFieldHudget> m_speedLabel;
    std::unique_ptr<ButtonHudget> m_targetName;

    std::list<Hudget*> m_hudgets;

    std::map<WorldObject*, HUDObjectDelegate*> m_objectDelegates;

    void updateScanner(float deltaSec);
    void updateFov();

    void callback(ClickType clicktype);
};


#pragma once

#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <vector>

#include "geometry/sphere.h"

#include "property/property.h"

#include "utils/handle/handle.h"


enum class ClickType {
    None,
    Selection
};

class Player;
class Hudget;
class WorldObject;
class HUDElements;
class HUDObjectDelegate;
class HudgetAnimation;
class HudgetHideAnimation;
class AimHelperHudget;
class Viewer;
class WorldTreeScanner;
class CrossHair;
class TextFieldHudget;
class View;

class HUD {
public:
    HUD(Player* player);
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

    void setView(const View* view);

    void onClick(ClickType clickType);

    void update(float deltaSec);
    void draw();

    glm::vec3 applyTo(const glm::vec3 &vertex) const;

    float fovy() const;
    float fovx() const;

    void showMissionInfo(const std::string& title, const std::string& caption);
    void showMissionMessage(const std::string& message);
    void showMessage(const std::string& message);


protected:
    Player* m_player;
    const View* m_view;
    Sphere m_sphere;
    Handle<WorldObject> m_target;
    Property<bool> m_drawHud;

    float m_fovy;
    float m_fovx;

    CrossHair* m_crossHair;
    AimHelperHudget* m_aimHelper;

    std::unique_ptr<WorldTreeScanner> m_scanner;
    std::unique_ptr<HUDElements> m_elements;

    std::map<WorldObject*, HUDObjectDelegate*> m_objectDelegates;


    void updateScanner(float deltaSec);
    void updateFov();
};


#pragma once

#include <set>


class HUD;
class WorldObject;

class HUDObjectFilterUpdate {
public:
    HUDObjectFilterUpdate(HUD* hud, const std::set<WorldObject*>& newWorldObjects, const std::set<WorldObject*>& obsoleteWorldObjects);

    void apply();


protected:
    HUD* m_hud;
    std::set<WorldObject*> m_newWorldObjects;
    std::set<WorldObject*> m_obsoleteWorldObjects;
};


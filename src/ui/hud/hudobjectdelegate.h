#pragma once

#include "worldobject/handle/handle.h"


class HUD;
class Hudget;
class WorldObject;

/*
    Handle to a WorldObject that also holds the Hudget this
    WorldObject is represented by on the Hudget
*/
class HUDObjectDelegate {
public:
    HUDObjectDelegate(HUD* hud, WorldObject* worldObject);

    HUD* hud();
    WorldObject* worldObject();
    Hudget* objectHudget();
    Hudget* arrowHudget();


protected:
    HUD* m_hud;
    Handle<WorldObject> m_worldObjectHandle;
    Hudget* m_objectHudget;
    Hudget* m_arrowHudget;
};


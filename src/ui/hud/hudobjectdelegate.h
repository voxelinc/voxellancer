#pragma once

#include "utils/handle/handle.h"


class HUD;
class Hudget;
class ObjectHudget;
class WorldObject;

/*
    Handle to a WorldObject that also references the Hudget this
    WorldObject is represented by on the HUD
*/
class HUDObjectDelegate {
public:
    HUDObjectDelegate(HUD* hud, WorldObject* worldObject, ObjectHudget* hudget);

    HUD* hud();
    WorldObject* worldObject();
    ObjectHudget* hudget();


protected:
    HUD* m_hud;
    Handle<WorldObject> m_worldObjectHandle;
    ObjectHudget* m_hudget;
};


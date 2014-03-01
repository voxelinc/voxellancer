#pragma once

#include "utils/handle/handle.h"


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
    Hudget& hudget();


protected:
    HUD* m_hud;
    Handle<WorldObject> m_worldObjectHandle;
    std::unique_ptr<Hudget> m_hudget;
};


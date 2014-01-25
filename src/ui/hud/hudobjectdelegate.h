#pragma once

#include "worldobject/worldobjecthandle.h"

class HUD;
class Hudget;

class HUDObjectDelegate {
public:
    HUDObjectDelegate(HUD* hud, WorldObject* worldObject);

    HUD* hud();
    WorldObject* worldObject();
    Hudget* hudget();


protected:
    HUD* m_hud;
    std::shared_ptr<WorldObjectHandle> m_worldObjectHandle;
    Hudget* m_hudget;
};


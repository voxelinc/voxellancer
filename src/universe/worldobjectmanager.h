#pragma once

#include "gameobjectmanager.h"

#include "worldobject/worldobject.h"


class Sector;
class WorldObject;

class WorldObjectManager : public GameObjectManager<WorldObject> {
public:
    WorldObjectManager(Sector& sector);
    virtual ~WorldObjectManager();


protected:
    Sector& m_sector;

    virtual void onObjectAddtition(WorldObject* object) override;
    virtual void onObjectRemoval(WorldObject* object) override;
};


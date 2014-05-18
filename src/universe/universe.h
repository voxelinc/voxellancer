#pragma once

#include <memory>

#include "utils/component.h"


class GameObjectManager;
class Player;
class ScriptEngine;
class Sector;

class Universe {
public:
    Universe();
    virtual ~Universe();

    Player& player();
    ScriptEngine& scriptEngine();
    FactionMatrix& factionMatrix();

    void addSector(const std::shared_ptr<Sector>& sector);

    void addFunctionalObject(FunctionalObject* object);

    void update(float deltaSec);


protected:
    std::list<std::shared_ptr<Sector>> m_sectors;

    Component<GameObjectManager<FunctionalObject>> m_functionalObjects;
    Component<Player> m_player;
    Component<ScriptEngine> m_scriptEngine;
    Component<FactionMatrix> m_factionMatrix;
};


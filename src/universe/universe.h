#pragma once

#include <memory>

#include "utils/component.h"


class Player;
class ScriptEngine;
class Sector;

class Universe {
public:
    Universe();
    virtual ~Universe();

    Player& player();
    ScriptEngine& scriptEngine();

    void addSector(const std::shared_ptr<Sector>& sector);

    void addElement(FunctionalWorldElement* element);

    void update(float deltaSec);


protected:
    std::list<std::shared_ptr<Sector>> m_sectors;

    Component<Player> m_player;
    Component<ScriptEngine> m_scriptEngine;

    std::list<glow::ref_ptr<FunctionalWorldElement>> m_functionalElements;
};

